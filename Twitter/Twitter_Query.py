# -*- coding: utf-8 -*-
import tweepy
import sys
import os
import json


def Twitter_Login(user_name):
	if (os.path.isfile('API_twitter_all.keys')):
		file = open('API_twitter_all.keys', 'r+')
		all_data = json.load(file)
		file.close()
	else:
		all_data = {}

	consumer_key="2YIdiuX1g8GyCGu0bkl2w"
	consumer_secret="NQm7aC0R7yYNyIgIGp9YkVl5whgqLr7yhNM7n13sCso"
	auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
    
	if all_data.get(user_name):
		data = all_data[user_name]
	else:
		print auth.get_authorization_url()
		verification_num = input("Please input the verification number: ")
		auth.get_access_token( verification_num )
		data = {}
		data["ACCESS_TOKEN"] = auth.access_token.key
		data["ACCESS_TOKEN_SECRET"] = auth.access_token.secret
		all_data[user_name] = data
		file = open('API_twitter_all.keys', 'w')
		json.dump(all_data, file)
		file.close()

	file = open('API_twitter.keys','w')
	json.dump(data,file)
	file.close()
	auth.set_access_token(data["ACCESS_TOKEN"], data["ACCESS_TOKEN_SECRET"])
	api = tweepy.API(auth)
	return api
       
def Twitter_Log():
	if (os.path.isfile('API_twitter.keys')):
		file = open('API_twitter.keys', 'r+')
		data = json.load(file)
	else:
		file = open('API_twitter.keys', 'w')
		data = {}

	consumer_key="2YIdiuX1g8GyCGu0bkl2w"
	consumer_secret="NQm7aC0R7yYNyIgIGp9YkVl5whgqLr7yhNM7n13sCso"

	auth = tweepy.OAuthHandler(consumer_key, consumer_secret)

	if data.get('ACCESS_TOKEN'):
		auth.set_access_token(data["ACCESS_TOKEN"], data["ACCESS_TOKEN_SECRET"])
	file.close()
	api = tweepy.API(auth) 
	return api

def GetTime(date):
    Time = {}
    Time['year'] = date.year
    Time['month'] = date.month
    Time['day'] = date.day
    Time['hour'] = date.hour
    Time['minute'] = date.minute
    Time['second']= date.second
    Time['weekday'] = date.weekday()
    return Time


def Favorite(api, tweet_id):
    text = api.create_favorite(tweet_id)
    return text

def HomeTimeline(api):
    public_tweets = api.home_timeline(count=100)
    Posts = []
    for tweet in public_tweets:
        Post = {}
        t_user = tweet.user

        Post['user_name'] = t_user.screen_name
        Post['id'] = tweet.id_str
        Post['content'] = tweet.text
        Time = GetTime(tweet.created_at)
        Post['time'] = Time
        Posts.append(Post)
    return Posts

def UserTimeline(api, name):
    public_tweets = api.user_timeline(screen_name=name,count=100)
    Posts = []
    for tweet in public_tweets:
        Post = {}
        t_user = tweet.author
        Post['user_name'] = t_user.screen_name
        Post['id'] = tweet.id_str
        Post['content'] = tweet.text
        Time = GetTime(tweet.created_at)
        Post['time'] = Time
        Posts.append(Post)
    return Posts

def Reply(api, tweet_id, text):
    user = api.get_status(tweet_id)
    content = '@' + user.author.screen_name + ': '+ unicode(text,'utf8')  
    public_tweets = api.update_status(status=content, in_reply_to_status_id=tweet_id)

def Query(api, request):
    public_tweets = api.search(request,{})
    Posts = []
    for tweet in public_tweets:
        Post = {}
        t_user = tweet.from_user

        Post['user_name'] = t_user
        Post['id'] = tweet.id_str
        Post['content'] = tweet.text
        Time = GetTime(tweet.created_at)
        Post['time'] = Time
        Posts.append(Post)
    return Posts


def QueryMyTimeline(api, request):
    request = unicode(request, "utf-8")
    Posts = HomeTimeline(api)
    new_Posts = []
    for p in Posts:
        if request in p['content']:
            new_Posts.append(p)

    return new_Posts


def QueryUserTimeline(api, user_name, request):
    request = unicode(request, "utf-8")
    Posts = UserTimeline(api, user_name)
    new_Posts = []
    for p in Posts:
        if request in p['content']:
            new_Posts.append(p)

    return new_Posts

def GetFriends(api):
    friends = api.friends()
    file_friend = open('FriendsList','w')
    for f in friends:
        file_friend.write(f.screen_name + '\n')
    file_friend.close()


if __name__ == '__main__':

    
    # == OAuth Authentication ==
    #
    # This mode of authentication is the new preferred way
    # of authenticating with Twitter.



    api = Twitter_Log()

    # If the authentication was successful, you should
    # see the name of the account print out

    # If the application settings are set for "Read and Write" then
    # this line should tweet out the message to your account's 
    # timeline. The "Read and Write" setting is on https://dev.twitter.com/apps
    #api.update_status('Updating using OAuth authentication via Tweepy!')


    argc = len (sys.argv)

    if argc == 1:
        #do normal get time line
        Posts = HomeTimeline(api)

        file2 = open('POST.json', 'w')
        output = json.dumps(Posts)
        file2.write(output)
        file2.close()
    if argc > 2:
        i = 2
        if cmp(sys.argv[1], 'query') == 0:
            my = False
            while i < argc:
                if sys.argv[i] == '-r':
                    i = i + 1
                    request = sys.argv[i]
                elif sys.argv[i] == '-u':
                    i = i + 1
                    user = sys.argv[i]
                elif sys.argv[i] == '-m':
                    my = True
                i = i + 1
                
            if 'request' in locals() and 'user' in locals():
                Posts = QueryUserTimeline(api, user, request)
            elif 'user' in locals():
                Posts = UserTimeline(api, user)
            elif 'request' in locals() and my:
                Posts = QueryMyTimeline(api, request)
            elif 'request' in locals() and not my:
                Posts = Query(api, request)
            elif my:
                Posts = HomeTimeline(api)
     
            file2 = open('POST.json', 'w')
            output = json.dumps(Posts)
            file2.write(output)
            file2.close()
      

                
        elif cmp(sys.argv[1] , 'reply') == 0:
            tweet_id = sys.argv[2]
            file3 = open('reply', 'r')
            content = file3.read()
            file3.close()
            Reply(api, tweet_id, content)
        elif cmp(sys.argv[1], 'like') == 0:
            tweet_id = sys.argv[2]
            Favorite(api ,tweet_id)
        elif cmp(sys.argv[1], 'login') == 0:
            api = Twitter_Login(sys.argv[2])
            GetFriends(api)



    
    #Posts = HomeTimeline(api)

    #request = 'rain'
    #Posts = QueryMyTimeline(api,request)

   # for p in Posts:
    #    print p['user_name']
     #   print p['content'].encode('utf-8')
      #  print p['time']
       # print p['id']

    

