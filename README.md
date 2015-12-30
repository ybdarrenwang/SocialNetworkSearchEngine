SocialNetworkSearchEngine
=========================

This was my final project for grad-school class "Design Pattern and Software Development" of National Taiwan University (NTU) in Spring 2012. This project was done in pair-programming. My partner, Yung-Hsiang Yang (Github ID: larry61410) implemented API calls to social networks with Python. And I, Yow-Bang Wang (Github ID: piscesfantasy), was in charge of framework design the remaining implementations with C++. The first version support search on Plurk and Twitter. Main functions include keyword/friend search, browsing search results, recommendation and reply.

[12.2015]
- Rewrote Twitter part (both C++ and Python) for new Twitter API and refactoring
- Removed Plurk

[Known issues]
- Enter without content in most situations would freeze.
- Require previous post at the first post, or next at the last, would freeze.
