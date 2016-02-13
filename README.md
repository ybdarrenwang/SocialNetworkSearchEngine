Social Network Search Engine
============================
Keyword/friend search, browse search results, like and reply on Facebook and Twitter.

Platforms
---------
Linux, OS X

Requirements
------------
- g++ 4.2 or higher
- Python 2.6 or higher
- pdflatex (for make doc)
- Doxygen (for make doxygen)

Installation
------------
1. Execute "make" or "make all" to create SocialNetworkSearchEngine.exe.
2. Execute "make clean" to remove build/ folder entirely.
3. Execute "make doc" to compile PDF manual (NOTE: pdflatex needed).
4. Execute "make doxygen" to create HTML pages explaining code structure (NOTE: Doxygen needed).

Quick Start
-----------

####`Preparation`

The folders "Plurk" and "Twitter" contains python scripts that will be called. Therefore to run this program, the folders "Plurk" and "Twitter" must be in the same directory.

We use the following Python libraries for Social Network API:
- Plurk: plurk-oauth by clsung, available at http://www.plurk.com/API
- Twitter: tweepy by joshthecoder, available at https://dev.twitter.com/docs/api

####`Login`

This program adopts interactive command line interface. For the first execution of {\it SocialNetworkSearchEngine.exe} you will see the messages below:

```
Initializing Twitter
Initializing Plurk
Warning: can't load query history log
Choose Social Network (type "exit" to quit):
```

Just type "Plurk" If you want to login Plurk (the initial must be upper case!) and press enter. Then you can input your id and password. If this is your first login with this program, after entering ID and password you will see something like this:

```
Open the following URL and authorize it
http://www.plurk.com/OAuth/authorize?oauth\_token=......
Input the verification number: 
```

Browse the authentication webpage to get the verification number. This procedure will run twice to get required access token, and the program would store the access token in the file "API\_plurk\_all.keys" and "API\_twitter.keys" in current directory.

####`Search`

After logging in you will see this:
```
Start the next query? [y/n]: 
```

You can choose "n" to logout, or choose "y" to begin a search. The program will ask if you need "Basic Search" or "Advanced Search":
```
Choose query mode (1.Basic, 2.Advanced): 
1. Basic Search: Search over all the public messages with a keyword.
2. Advanced Search: Search over all the messages of your friends with a keyword and a friend's ID.
```

####`Auto-complete`

While entering either keyword or a friend's ID, this program also support auto-complete. For keyword the program will search and iterate through your most recent 100 queries stored in the file "queryHistory.log" in current folder; and for friend's ID the program will search and iterate through your friend lis stored in the file "FriendsList" in current folder. 

Yet for now this function is normal only for English words. There may be some unexpected error if you try to auto-complete non-English words.

####`Interact with posts`

After entering your query, the program will retrieve relevant posts and store them in the file "POST.json" in current folder. The first post will be shown on the screen followed by some options:
```
Whats next?
- Pu this post [l]
- Reply this post [r]
- Go to next post [n]
- Quit browsing [q]
```

If you are browsing posts except the first one, the option will also includes:
```
- Go to previous post [p]
```

Just enter the option in the bracket to execute.

####`Terminate`

To terminate the program, just type "exit" when you are not logged in any social network.

####`System framework and design patterns`

![patterns](https://github.com/piscesfantasy/SocialNetworkSearchEngine/blob/master/doc/classDiagram.png)

1. class User: Singleton
2. class SocialNet: Singleton + Prototype Manager + Abstract Factory
3. class Query: Command + Template Method
4. class Post: Decorator 

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
- Not yet updated manual to latest version
- Enter without content in most situations would keep program waiting without hints output, makes it look like freezing.
