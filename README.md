Social Network Search Engine
============================

This was my final project for grad-school class "Design Pattern and Software Development" of National Taiwan University (NTU) in Spring 2012. This project was done in pair-programming. My partner, Yung-Hsiang Yang (Github ID: larry61410) implemented API calls to social networks with Python. And I, Yow-Bang Wang (Github ID: piscesfantasy), was in charge of framework design the remaining implementations with C++. The first version support search on Plurk and Twitter. Main functions include keyword/friend search, browsing search results, recommendation and reply.

[12.2015]
- Rewrote Twitter (both C++ and Python) for new API and refactoring.
- Removed Plurk.

[01.2016]
- Added Facebook.
- Note: Facebook API does not allow to retrieve friends list, therefore can't auto-complete user name.
- Note: Facebook API does not allow to retrieve posts on friends' walls, therefore search friend by [NAME] is identical to search keyword [NAME] on user's own wall.

[Known issues]
- doc/manual.pdf not yet updated
- Enter without content in most situations would keep program waiting without hints output, makes it look like freezing.
