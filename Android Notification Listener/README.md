# Notification Listener

This tutorial shows you how to make your phone actively listen to notifications—not just display them as usual—but capture (scrape) their content, convert it into a JSON file, and send it anywhere you need.

This approach is especially useful if you want to use your phone as a bridge to applications or workflows that don’t exist (or can’t access notifications) in a PC environment—enabling automation, remote logging, or custom integrations.



### Things that you need
You don’t need many apps—just one that’s capable and easy to find.
Right now, I’m working with Android, but I may develop an iOS version later on.

> Search on Google play "Microdroid"
<p align="left">
  <img src="./Image/PlayStore%20Microdroid.jpg" width="250" />
</p>


I know there are other ways to do this—like using Termux to run scripts or integrating with other automation apps—but I’m using this method because it’s already working for me. I’ve tested it, and it succeeds.


### Tutorials
Once you’ve installed Microdroid, make sure to follow each step exactly the way I’m doing it right now. Missing even one could cause problems.
But don’t worry—I’ll add pictures for the trickier parts!

1. Open the application, then go to the Macros tab at the bottom of the screen. Tap the "+" symbol to add a new macro.
After that, you’ll see several sections appear—such as Triggers, Actions, Constraints, and Local Variables.
<p align = "left">
  <img src="./Image/Macros%20Lobby(2).jpg" width="250">
</p>

3. After that, tap the "+" symbol in the Triggers section, select Device Event > Notification > Received, choose the application, optionally enter a keyword in the "Enter text to match" field (or adjust other settings) to filter which notifications get captured, then tap OK.
<p align = "left">
  <img src="./Image/Trigers%20Picture.jpg" width="250">
</p>

5. This the main things that you must more carefully, Add Action > Variables > Set Variable > [New Variable] > Put name (example : "data") > Set Variable Type to String > Press ok > Copy paste these data
```
{
"app":"{not_app_name}",
"tiitle":"{not_title}",
"text":"Notification}"
}
```
  if error that might be error key variable u can search manually on "..." Button

4. After setting the parsing data, it’s time to post it: go to Actions > Web Interaction > HTTP Request, set the method to POST, enter your webhook URL, tap Content Body, paste your JSON payload like {Data} (or your desired format), then tap Done.
<p align = "left">
  <img src="./Image/Actions%20Picture.jpg" width="250">
</p>  
  Once saved, your macro will run automatically—just trigger a test notification to check if the notification data is successfully sent to your webhook.  
  
### Note
* I’m updating this repo on November 18, 2025, using MacroDroid version 5.58.13—layouts may differ in newer versions.
* If you find any outdated or incorrect steps, feel free to submit a pull request or DM me (contact info is in my bio).
* The app is free initially, but after extended use it may require payment; you can extend access with a 3-day free trial by watching a video, or unlock it permanently with a one-time purchase (around $2, though prices may vary by country).
