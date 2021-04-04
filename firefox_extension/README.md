## Design Goal

To write a browser extension, which acts as the last defense mechanism on the client side, to prevent user from being attacked. Assuming attacker is able to inject arbitrary JavaScript code on the wordpress, the attacker is not able to get remote code execution on the server.

## Design Rationale

When wordpress administrators making legitimate action, the path in the address bar and the path of the request being sent forms a mapping, this mapping can act as an indicator of whether the request being sent is normal or abnormal.

For example:
When he is editing the theme files, his path in the address bar would be `/wp-admin/theme-editor.php`, and he would send a post request to `/wp-admin/admin-ajax.php`, with parameter `_wp_http_referer` = `/wp-admin/theme-editor.php`, `action` = `edit-theme-plugin-file`. If an administrator sends a theme-editing request when his path indicates that he is actually reading a post, this abnormal behavior is a strong evidence that he is being attacked at the client-side. Some one/scripts is impersonating his identity to modify the web files. This request should be caught and stopped, and the user can be notified/warned. All this can be done at the lower layer, where the browser extension comes into a perfect play.

Now, the crucial part is: How to find the mappings between the path in the address bar and the path of the request being sent, during a legitimate action? We have concluded some, which might not be enough, so we allow administrator to add in their own mapping rules in the future to fit their needs (For example, administrator might want to protect himself from posting a fake article by the malicious JavaScript, he can then add his own mapping).

Mappings of sensitive operations:

| action            | path in address bar         | path of the request      | parameter                     |
| ----------------- | --------------------------- | ------------------------ | ----------------------------- |
| edit theme files  | /wp-admin/theme-editor.php  | /wp-admin/admin-ajax.php | action=edit-theme-plugin-file |
| edit plugin files | /wp-admin/plugin-editor.php | /wp-admin/admin-ajax.php | action=edit-theme-plugin-file |
| add user          | /wp-admin/user-new.php      | /wp-admin/user-new.php   | action=createuser             |
| change password   | /wp-admin/profile.php       | /wp-admin/profile.php    | from=profile                  |

