function saveOptions(e) {
    e.preventDefault();
    browser.storage.sync.set({
        mapping: document.getElementById("mapping").value,
        url: document.getElementById("url").value
    });
    // send the updated urls and mappings to the background script.
    var sending = browser.runtime.sendMessage([document.getElementById("url").value,document.getElementById("mapping").value])
}

function restoreOptions() {

    function setCurrentMapping(result) {
        //console.log(result.mapping);
        document.getElementById("mapping").value = result.mapping || "{}";
    }

    function setCurrentUrl(result) {
        //console.log(result.url);
        document.getElementById("url").value = result.url || "[]";
    }

    function onError(error) {
        console.log(`Error: ${error}`);
    }

    let getting1 = browser.storage.sync.get("mapping");
    getting1.then(setCurrentMapping, onError);
    let getting2 = browser.storage.sync.get("url");
    getting2.then(setCurrentUrl, onError);
}

document.addEventListener("DOMContentLoaded", restoreOptions);
document.querySelector("button").addEventListener("click", saveOptions);

