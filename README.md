Social Network Search Engine
============================
Keyword/friend search, browse search results, like and reply on Facebook and Twitter.

[06/2012]
- First version: final project for class "Design Pattern and Software Development" of National Taiwan University (NTU), done in pair-programming. My partner, Yung-Hsiang Yang (Github ID: larry61410) implemented API calls to social networks with Python; and I was in charge of framework design the remaining implementations with C++.
- Support search on Plurk and Twitter. Main functions include keyword/friend search, browsing search results, recommendation and reply.

[12/2015]
- Rewrote Twitter (both C++ and Python) for new API and refactoring.
- Removed Plurk.

[01/2016]
- Added Facebook.
- Note: Facebook API does not allow to retrieve friends list, therefore can't auto-complete user name.
- Note: Facebook API does not allow to retrieve posts on friends' walls, therefore search friend by [NAME] is identical to search keyword [NAME] on user's own wall.

[Known issues]
- doc/manual.pdf not yet updated
- Enter without content in most situations would keep program waiting without hints output, makes it look like freezing.
