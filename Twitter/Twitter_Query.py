#!/usr/bin/python
# coding: utf-8
import tweepy
import sys, os, json
from optparse import OptionParser

reload(sys)  
sys.setdefaultencoding('utf8')
	
consumer_key="2YIdiuX1g8GyCGu0bkl2w"
consumer_secret="NQm7aC0R7yYNyIgIGp9YkVl5whgqLr7yhNM7n13sCso"
tmp_folder = "log/twitter"

def userLogin(user_name):
    all_users_auth = {}
    current_auth = {}
    os.system('rm -rf %s/current_user.log' % tmp_folder)
    if user_name: # try to load user auth from cache
        if os.path.isfile(tmp_folder+'/users.json'):
            all_users_auth = json.load(open(tmp_folder+'/users.json'))
            if all_users_auth.get(user_name):
                current_auth = all_users_auth[user_name]
        open(tmp_folder+'/current_user.log','w').write(user_name)
    else:
        exit("ERROR: Please login with --login [USERNAME].")

    auth = tweepy.OAuthHandler(consumer_key, consumer_secret)
    if not current_auth: # new user, ask for auth and save to cache
        print auth.get_authorization_url()
        verification_num = str(input("Please input the verification number: "))
        auth.get_access_token( verification_num )
        current_auth["ACCESS_TOKEN"] = auth.access_token
        current_auth["ACCESS_TOKEN_SECRET"] = auth.access_token_secret
        all_users_auth[user_name] = current_auth
        json.dump(all_users_auth, open(tmp_folder+'/users.json', 'w'))
    auth.set_access_token(current_auth["ACCESS_TOKEN"], current_auth["ACCESS_TOKEN_SECRET"])
    return tweepy.API(auth)

def currentUserLogin():
    try:
        user_name = open(tmp_folder+'/current_user.log').readline()
        return userLogin(user_name)
    except:
        exit("ERROR: Can't find user login info. Please login with --login [USERNAME].")

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

def getPosts(public_tweets):
    posts = []
    for tweet in public_tweets:
        post = {}
        post['user_name'] = tweet.author.screen_name
        post['id'] = tweet.id_str
        post['content'] = tweet.text
        post['time'] = getTime(tweet.created_at)
        posts.append(post)
    return posts

def getMyTimeline(api):
    return getPosts(api.home_timeline(count=100))

def getUserTimeline(api, name):
    return getPosts(api.user_timeline(screen_name=name,count=100))

def queryAll(api, query):
    return getPosts(api.search(query,{}))

def queryMyTimeline(api, query):
    return [p for p in getMyTimeline(api) if unicode(query, "utf-8") in p['content']]

def queryUserTimeline(api, user_name, query):
    return [p for p in getUserTimeline(api, user_name) if unicode(query, "utf-8") in p['content']]

def favorite(api, tweet_id):
    return api.create_favorite(tweet_id)

def reply(api, tweet_id, text):
    user = api.get_status(tweet_id)
    content = '@' + user.author.screen_name + ': '+ unicode(text,'utf8')  
    public_tweets = api.update_status(status=content, in_reply_to_status_id=tweet_id)

def saveFriendsList(api):
    open('log/friends.list','w').write('\n'.join([f.screen_name for f in api.friends()]))

def savePosts(posts):
    open(tmp_folder+'/posts.json', 'w').write(json.dumps(posts))

if __name__ == '__main__':
    """
    Use cached user as default; override cached user by --login USER_ID
    """
    os.system('mkdir -p '+tmp_folder)
    parser = OptionParser()
    parser.add_option("--login", dest="login", default=None,
                        help="New user ID to login")
    parser.add_option("--search", dest="search", action="store_true", default=False,
                        help="Search with --query, --user or --own")
    parser.add_option("--query", dest="query", default=None, help="The query to search")
    parser.add_option("--user", dest="user", default=None, help="The user ID to search")
    parser.add_option("--own", dest="onlySearchMyposts", action="store_true", default=False,
                        help="Limit search to current user's posts")
    parser.add_option("--reply", dest="reply", default=None,
                        help="Reply the post")
    parser.add_option("--like", dest="like", default=None,
                        help="Like the post")
    (options, args) = parser.parse_args()
    if options.login: # override cached user
        user = userLogin(options.login)
        saveFriendsList(user)
    elif options.search:
        posts = None
        if options.user:
            if options.query:
                posts = queryUserTimeline(currentUserLogin(), options.user, options.query)
            else:
                posts = getUserTimeline(currentUserLogin(), options.user)
        elif options.query:
            if options.onlySearchMyposts:
                posts = queryMyTimeline(currentUserLogin(), options.query)
            else:
                posts = queryAll(currentUserLogin(), options.query)
        elif options.onlySearchMyposts: 
            posts = getMyTimeline(currentUserLogin())
        savePosts(posts)
    elif options.reply:
        reply(currentUserLogin(), options.reply, open('log/twitter/reply.txt', 'r').read())
    elif options.like:
        favorite(currentUserLogin(), options.like)
    else:
        posts = getMyTimeline(currentUserLogin())
        savePosts(posts)
