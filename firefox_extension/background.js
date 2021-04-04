// pre-set mapping
var mapping_str = "{\n    \"/wp-admin/admin-ajax.php\":{\n        \"action=edit-theme-plugin-file\":[\n            \"/wp-admin/theme-editor.php\",\n            \"/wp-admin/plugin-editor.php\"\n        ]\n    },\n    \"/wp-admin/user-new.php\":{\n        \"action=createuser\":[\n            \"/wp-admin/user-new.php\"\n        ]\n    },\n    \"/wp-admin/profile.php\":{\n        \"from=profile\":[\n            \"/wp-admin/profile.php\"\n        ]\n    }\n}";
var mapping = JSON.parse(mapping_str);

// pre-set target
var target_str = "[\"http://localhost/\"]";
var target = JSON.parse(target_str);

// save to localstorage.
browser.storage.sync.set({
    mapping: mapping_str,
    url: target_str
});

async function Check(requestDetails) {
    // tabInfo.url provides more general approach than requestDetails.documentURL and requestDetails.originUrl, where the last two can be forged to be a legitimate operation request and hence bypass the check, so far I can't think of bypass scenario for tabInfo.url.
    // for requestDetails.documentURL, a top-level form post will makes it empty/undefined, which is the case for a legitimate password resetting and adding user operation.
    // for requestDetails.originUrl, iframing a correct page and send the request from that iframe would forge the requestDetails.originUrl to be the URI of the correct page and hence bypass the check as well.
    // tabInfo.url requires additional permission though.

    // sensitive operation involves POSTing data.
    if (!requestDetails.requestBody) {
        return;
    }
    var data = requestDetails.requestBody.formData;

    let tabInfo = await browser.tabs.get(requestDetails.tabId);
    if (!tabInfo) {
        return;
    }

    var tabPath = (new URL(tabInfo.url)).pathname;
    var requestPath = (new URL(requestDetails.url)).pathname;

    // if requestPath does not exists in our mapping, skip checking!
    if (!mapping[requestPath]) {
        return;
    }

    for (const postData in mapping[requestPath]) {
        var [parameter, value] = postData.split("=");
        if (data[parameter][0] == value) {
            // if the tabPath does not match
            if (!mapping[requestPath][postData].includes(tabPath)) {
                console.log("gotcha");

                // send message to warn the user.
                chrome.tabs.sendMessage(requestDetails.tabId,"Blocked request to "+requestPath+" with data " + postData + " when you are at "+tabPath);

                // cancel this request!
                return {
                    "cancel":"true"
                }
            }
        }
    }
}

chrome.webRequest.onBeforeRequest.addListener(
    Check,
    {
        urls: target,
        types: ["main_frame", "sub_frame", "xmlhttprequest"]
    },
    ["blocking", "requestBody"]
);

// register onclick event to open the preference setting page.
browser.browserAction.onClicked.addListener(handleClick);

function handleClick() {
    browser.runtime.openOptionsPage();
}

browser.runtime.onMessage.addListener(updateConfig);

function updateConfig(data, sender) {
    mapping = JSON.parse(data[1]);

    // reload target
    target = [];
    for (var url of JSON.parse(data[0])) {
        // remove the trailing `/`
        if (url.slice(-1) == '/') {
            url = url.slice(0, -1);
        }
        // all pages under the domain.
        target.push(url + "/*");
    }

    // need to reload the listener in case the urls changed!
    chrome.webRequest.onBeforeRequest.removeListener(Check);
    chrome.webRequest.onBeforeRequest.addListener(
        Check,
        {
            urls: target,
            types: ["main_frame", "sub_frame", "xmlhttprequest"]
        },
        ["blocking", "requestBody"]
    );

    return;
}
