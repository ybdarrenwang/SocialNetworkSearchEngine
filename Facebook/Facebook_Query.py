#!/usr/bin/python
# coding: utf-8
import facebook
import sys, os, json
from optparse import OptionParser

reload(sys)  
sys.setdefaultencoding('utf8')

app_id       = '1226220920740227'
app_secret   = '24f99662865dd4302974a4d1ee8f5ce2'
perms        = ['user_friends','user_posts','publish_actions']
redirect_uri = "https://www.facebook.com/"
tmp_folder = "log/facebook"

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

    if not current_auth: # new user, ask for auth and save to cache
        print facebook.auth_url(app_id, redirect_uri, perms)
        code = str(raw_input("Please copy and paste the verification number following https://www.facebook.com/?code= "))
        access_token = facebook.get_access_token_from_code(code, redirect_uri, app_id, app_secret)["access_token"]
        current_auth["ACCESS_TOKEN"] = access_token
        all_users_auth[user_name] = current_auth
        json.dump(all_users_auth, open(tmp_folder+'/users.json', 'w'))
    return facebook.GraphAPI(current_auth["ACCESS_TOKEN"])

def currentUserLogin():
    try:
        user_name = open(tmp_folder+'/current_user.log').readline()
        return userLogin(user_name)
    except:
        exit("ERROR: Can't find user login info. Please login with --login [USERNAME].")

def getTime(date):
    token = date.split('T')
    Time = {}
    [Time['year'], Time['month'], Time['day']] = [int(x) for x in token[0].split('-')]
    [Time['hour'], Time['minute'], Time['second']] = [int(x) for x in token[1].split('+')[0].split(':')]
    Time['weekday'] = -1
    return Time

def getPosts(my_posts):
    posts = []
    for p in my_posts:
        post = {}
        post['user_name'] = ''
        post['id'] = p['id']
        if 'message' not in p: p['message'] = ''
        if 'story' not in p: p['story'] = ''
        post['content'] = '%s\n%s' % (p['message'], p['story'])
        post['time'] = getTime(p['created_time'])
        posts.append(post)
    return posts

def getMyTimeline(api):
    return getPosts(api.get_object('me/feed')['data'])

def getUserTimeline(api, name):
    return [p for p in getMyTimeline(api) if unicode(name, "utf-8") in p['content']]

def queryMyTimeline(api, query):
    return [p for p in getMyTimeline(api) if unicode(query, "utf-8") in p['content']]

def queryUserTimeline(api, user_name, query):
    return [p for p in getUserTimeline(api, user_name) if unicode(query, "utf-8") in p['content']]

def favorite(api, post_id):
    api.put_like(post_id)

def reply(api, post_id, text):
    api.put_comment(post_id, text)

def savePosts(posts):
    open(tmp_folder+'/posts.json', 'w').write(json.dumps(posts))


if __name__ == '__main__':
    """
    Use cached user as default; override cached user by --login USER_ID
    Note: Facebook API only allows to read/write current user's wall
    """
    os.system('mkdir -p '+tmp_folder)
    parser = OptionParser()
    parser.add_option("--login", dest="login", default=None,
                        help="New user ID to login")
    parser.add_option("--search", dest="search", action="store_true", default=False,
                        help="Search with --query, --user or --own")
    parser.add_option("--query", dest="query", default=None, help="The query to search")
    parser.add_option("--user", dest="user", default=None, help="The user ID to search")
    parser.add_option("--reply", dest="reply", default=None,
                        help="Reply the post")
    parser.add_option("--like", dest="like", default=None,
                        help="Like the post")
    (options, args) = parser.parse_args()
    if options.login: # override cached user
        user = userLogin(options.login)
    elif options.search:
        posts = None
        if options.user:
            if options.query:
                posts = queryUserTimeline(currentUserLogin(), options.user, options.query)
            else:
                posts = getUserTimeline(currentUserLogin(), options.user)
        elif options.query:
            posts = queryMyTimeline(currentUserLogin(), options.query)
        else: 
            posts = getMyTimeline(currentUserLogin())
        savePosts(posts)
    elif options.reply:
        reply(currentUserLogin(), options.reply, open('log/facebook/reply.txt', 'r').read())
    elif options.like:
        favorite(currentUserLogin(), options.like)
    else:
        posts = getMyTimeline(currentUserLogin())
        savePosts(posts)
