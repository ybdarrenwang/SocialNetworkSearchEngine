Social Network Search Engine
============================
Keyword/friend search, browse search results, like and reply on Facebook and Twitter.

Platforms
---------
Linux, OS X

Requirements
------------
* g++ 4.2 or higher
* Python 2.6 or higher
  * Note: need `Requests` module for Twitter's API
    * On Linux: `sudo pip install requests` (if you have pip installed)
    * On OS X: `sudo easy_install -U requests` (if you have easy\_install installed)
* Doxygen (for make doxygen)

Installation
------------
1. `make` or `make all` to create SocialNetworkSearchEngine.exe.
2. `make clean` to remove build/ folder entirely.
3. `make doxygen` to create HTML pages explaining code structure (NOTE: Doxygen needed).

Quick Start
-----------

### Preparation

The folders `Facebook` and `Twitter` contain python scripts that will be called by the executable. Therefore to run this program, the folders "Facebook" and "Twitter" must be under the same directory.

We use the following Python libraries for Dialog OAuth API:
* Facebook: Facebook Graph API, available at https://github.com/pythonforfacebook/facebook-sdk
* Twitter: Tweepy by joshthecoder, available at https://github.com/tweepy/tweepy

You need to create your own Facebook or Twitter app by yourself:
* Facebook: https://developers.facebook.com/apps/
* Twitter: https://apps.twitter.com/

After getting the app ID (public key) and secret key (private key), update the variables `app_id` and `app_secret` respectively in:
* `Facebook/Facebook_Query.py`
* `Twitter/Twitter_Query.py`

### Login

This program adopts interactive command line interface. After execution of `SocialNetworkSearchEngine.exe` you will see the messages below:
```
Initializing Twitter
Initializing Facebook
Warning: can't load query log/history.log
Enter "Facebook" or "Twitter" to begin, or "exit" to quit:
```
Just type "Facebook" If you want to login Facebook (the initial must be upper case!) and press enter, then type in your ID. If this is your first login with this program, you should see the prompt message requiring your authorization through Dialog OAuth.

For Facebook, the message looks like below:
```
Login Facebook with id=......
https://www.facebook.com/dialog/oauth?scope=user_friends%2Cuser_posts%2Cpublish_actions&redirect_uri=https%3A%2F%2Fwww.facebook.com%2F&client_id=......
Please copy and paste the verification number following https://www.facebook.com/?code=
```
1. Open the url with browser;
2. Allow the permissions;
3. You should be redirected to url `https://www.facebook.com/?code=[VERIFICATION NUMBER]`;
4. Copy the `[VERIFICATION NUMBER]` part in url, paste it after this message, and press enter.

For Twitter, the message looks like below:
```
Login Twitter with id=......
https://api.twitter.com/oauth/authorize?oauth_token=......
Please input the verification number:
```
1. Open the url with browser;
2. Allow the permissions;
3. You should be redirected to a webpage with verification number in the middle;
4. Enter the verification number after this message. (warning: don't copy and paste!)

###Search

After logging in you should see the message:
```
Login succeeded
Start the next query? [y/n]: 
```

You can choose "n" to logout, or choose "y" to begin a search. The program will ask if you need "Basic Search" or "Advanced Search":
```
Choose query mode (1.Basic, 2.Advanced):
```
1. Basic Search: Search over all posts on your wall (Facebook) or all tweets (Twitter) with a keyword.
2. Advanced Search:
  * Facebook: becasue Facebook API does not allow to retrieve posts on friends' walls, therefore search friend by [NAME] is identical to search keyword [NAME] on your own wall.
  * Twitter: can assign a friend's ID, and then search over all of his/her messages of with a keyword.

###Auto-complete

While entering either keyword or a friend's ID, this program also support auto-complete. For keyword the program will search and iterate through your most recent 100 queries stored in the file `./log/history.log`; and for friend's ID the program will search and iterate through your friend lis stored in the file `./log/friends.list`.

Yet for now this function is normal only for English words. There may be some unexpected error if you try to auto-complete non-English words.

###Interact with posts

Take `Basic Search` on `Facebook` as example. After entering your query, the program will retrieve relevant posts and store them in the file `./log/facebook/posts.json`. The first post will be shown on the screen followed by some options:
```
Whats next?
- like this post [l]
- Reply this post [r]
- Go to next post [n]
- Quit browsing [q]
```
If you are browsing posts except the first one, the option will also includes:
```
- Go to previous post [p]
```
Just enter the option in the bracket to execute.

###Terminate

Enter `exit` when you are not logged in any social network.

System framework and design patterns
------------------------------------

![patterns](https://github.com/piscesfantasy/SocialNetworkSearchEngine/blob/master/doc/classDiagram.png)

Release Notes
-------------

[01/2016]
- Added Facebook.
- Note: Facebook API does not allow to retrieve friends list, therefore can't auto-complete user name.
- Note: Facebook API does not allow to retrieve posts on friends' walls, therefore search friend by [NAME] is identical to search keyword [NAME] on user's own wall.

____________
[12/2015]
- Rewrote Twitter (both C++ and Python) for new API and refactoring.
- Removed Plurk.

____________
[06/2012]
- First version: final project for class "Design Pattern and Software Development" of National Taiwan University (NTU), done in pair-programming. My partner, Yung-Hsiang Yang (Github ID: larry61410) implemented API calls to social networks with Python; and I was in charge of framework design the remaining implementations with C++.
- Support search on Plurk and Twitter. Main functions include keyword/friend search, browsing search results, recommendation and reply.

Known issues
------------
- Enter without content in most situations would keep program waiting without hints output, makes it look like freezing.
