# -*- coding: utf-8 -*-
import tweepy
import sys
import os
import json
	
consumer_key="2YIdiuX1g8GyCGu0bkl2w"
consumer_secret="NQm7aC0R7yYNyIgIGp9YkVl5whgqLr7yhNM7n13sCso"

def userLogin(user_name):
    all_users_auth = {}
    current_auth = {}
    if user_name: # try to load user auth from cache
        if os.path.isfile('twitter_users.json'):
            all_users_auth = json.load(open('twitter_users.json'))
            if all_users_auth.get(user_name):
                current_auth = all_users_auth[user_name]
        open('twitter_current_user.log','w').write(user_name)

    auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
    if not current_auth: # new user, ask for auth and save to cache
        print auth.get_authorization_url()
        verification_num = str(input("Please input the verification number: "))
        auth.get_access_token( verification_num )
        current_auth["ACCESS_TOKEN"] = auth.access_token
        current_auth["ACCESS_TOKEN_SECRET"] = auth.access_token_secret
        all_users_auth[user_name] = current_auth
        json.dump(all_users_auth, open('twitter_users.json', 'w'))
    auth.set_access_token(current_auth["ACCESS_TOKEN"], current_auth["ACCESS_TOKEN_SECRET"])
    return tweepy.API(auth)

def currentUserLogin():
    if os.path.isfile('twitter_current_user.log'):
        user_name = open('twitter_current_user.log').readline()
        return userLogin(user_name)
    return None

def getTime(date):
    Time = {}
    Time['year'] = date.year
    Time['month'] = date.month
    Time['day'] = date.day
    Time['hour'] = date.hour
    Time['minute'] = date.minute
    Time['second']= date.second
    Time['weekday'] = date.weekday()
    return Time

def getMyTimeline(api):
    print 'getMyTimeline'
    public_tweets = api.home_timeline(count=100)
    Posts = []
    for tweet in public_tweets:
        Post = {}
        Post['user_name'] = tweet.user.screen_name
        Post['id'] = tweet.id_str
        Post['content'] = tweet.text
        Post['time'] = getTime(tweet.created_at)
        Posts.append(Post)
    return Posts

def getUserTimeline(api, name):
    print 'getUserTimeline'
    public_tweets = api.user_timeline(screen_name=name,count=100)
    Posts = []
    for tweet in public_tweets:
        Post = {}
        Post['user_name'] = tweet.author.screen_name
        Post['id'] = tweet.id_str
        Post['content'] = tweet.text
        Post['time'] = getTime(tweet.created_at)
        Posts.append(Post)
    return Posts

def queryAll(api, keyword):
    print 'queryAll'
    public_tweets = api.search(keyword,{})
    Posts = []
    for tweet in public_tweets:
        Post = {}
        Post['user_name'] = tweet.author.screen_name
        Post['id'] = tweet.id_str
        Post['content'] = tweet.text
        Post['time'] = getTime(tweet.created_at)
        Posts.append(Post)
    return Posts

def queryMyTimeline(api, keyword):
    print 'queryMy'
    return [p for p in getMyTimeline(api) if unicode(keyword, "utf-8") in p['content']]

def queryUserTimeline(api, user_name, keyword):
    print 'queryUser'
    return [p for p in getUserTimeline(api, user_name) if unicode(keyword, "utf-8") in p['content']]

def favorite(api, tweet_id):
    return api.create_favorite(tweet_id)

def reply(api, tweet_id, text):
    user = api.get_status(tweet_id)
    content = '@' + user.author.screen_name + ': '+ unicode(text,'utf8')  
    public_tweets = api.update_status(status=content, in_reply_to_status_id=tweet_id)

def saveFriendsList(api):
    open('FriendsList','w').write('\n'.join([f.screen_name for f in api.friends()]))

def savePosts(posts):
    open('POST.json', 'w').write(json.dumps(posts))

if __name__ == '__main__':
    api = currentUserLogin()
    argc = len (sys.argv)
    if argc == 1: #do normal get time line
        savePosts(getTimeline(api))
    if argc > 2:
        i = 2
        if cmp(sys.argv[1], 'query') == 0:
            onlySearchMyPosts = False
            while i < argc:
                if sys.argv[i] == '-r':
                    i += 1
                    keyword = sys.argv[i]
                elif sys.argv[i] == '-u':
                    i += 1
                    user = sys.argv[i]
                elif sys.argv[i] == '-m':
                    onlySearchMyPosts = True
                i += 1
            if 'user' in locals():
                if 'request' in locals():
                    Posts = queryUserTimeline(api, user, keyword)
                else:
                    Posts = getUserTimeline(api, user)
            elif 'request' in locals():
                if onlySearchMyPosts:
                    Posts = queryMyTimeline(api, keyword)
                else:
                    Posts = queryAll(api, keyword)
            elif onlySearchMyPosts:
                Posts = getMyTimeline(api)
            savePosts(Posts)
        elif cmp(sys.argv[1] , 'reply') == 0:
            reply(api, sys.argv[2], open('reply', 'r').read())
        elif cmp(sys.argv[1], 'like') == 0:
            favorite(api, sys.argv[2])
        elif cmp(sys.argv[1], 'login') == 0:
            saveFriendsList(userLogin(sys.argv[2]))
