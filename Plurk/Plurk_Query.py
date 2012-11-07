# -*- coding: utf-8 -*-
import sys
import os
sys.path.append('plurk_oauth/')
from PlurkAPI import PlurkAPI
import getopt
import json

Month_dic = {
    'Jan' : 1,
    'Feb' : 2,
    'Mar' : 3,
    'Apr' : 4,
    'May' : 5,
    'Jun' : 6,
    'Jul' : 7,
    'Aug' : 8,
    'Sep' : 9,
    'Oct' : 10,
    'Nov' : 11,
    'Dec' : 12
    }


def usage():
    print '''Help Information:
    -h: Show help information
    '''
def Plurk_Login(user_name):
	if (os.path.isfile('API_plurk_all.keys')):
	    file = open('API_plurk_all.keys', 'r+')
	    all_data = json.load(file)
	    file.close()
	else:
		all_data = {}

	consumer_key = "8GR4shW16mNX"
	consumer_secret = "2DSFSK5vHEva2LsxjDYaKpISu2pYCjNy"
	plurk = PlurkAPI(consumer_key, consumer_secret)

	if all_data.get(user_name):
		data = all_data[user_name]
	else:
		plurk.authorize()
		data = {}
		data["ACCESS_TOKEN"] = plurk._oauth.oauth_token['oauth_token']
		data["ACCESS_TOKEN_SECRET"] = plurk._oauth.oauth_token['oauth_token_secret']
		all_data[user_name] = data
		file = open('API_plurk_all.keys', 'w')
		json.dump(all_data, file)
		file.close()

	file = open('API_plurk.keys','w')
	json.dump(data,file)
	file.close()
	plurk.authorize(data["ACCESS_TOKEN"],data["ACCESS_TOKEN_SECRET"])
	return plurk
       
def Plurk_Log():
	if (os.path.isfile('API_plurk.keys')):
		file = open('API_plurk.keys', 'r+')
		data = json.load(file)
	else:
		file = open('API_plurk.keys', 'w')
		data = {}
	consumer_key = "8GR4shW16mNX"
	consumer_secret = "2DSFSK5vHEva2LsxjDYaKpISu2pYCjNy"
	plurk = PlurkAPI(consumer_key, consumer_secret)
	if data.get('ACCESS_TOKEN'):
		plurk.authorize(data["ACCESS_TOKEN"],data["ACCESS_TOKEN_SECRET"])
	else:
		plurk.authorize()
		data["ACCESS_TOKEN"] = plurk._oauth.oauth_token['oauth_token']
		data["ACCESS_TOKEN_SECRET"] = plurk._oauth.oauth_token['oauth_token_secret']
	file.close()
	return plurk

def ParseTime(d):
    date = d.split()
    Time = {}
    Time['day'] = int(date[1])
    Time['month'] = Month_dic[date[2]]
    Time['year'] = int(date[3])
    Time['week_day'] = date[0].strip(',')

    accurate_time = date[4].split(':')        
    Time['hour'] = int( accurate_time[0])
    Time['minute'] = int( accurate_time[1])
    Time['second'] = int( accurate_time[2])

    return Time

def GetFriends(plurk):
    user = plurk.callAPI('/APP/Users/currUser')
    uid = user["id"]
    n = 99
    off_num = 0
    file_friend = open('FriendsList','w')
    while n >= 99:
        friends = plurk.callAPI('/APP/FriendsFans/getFriendsByOffset',{
                           'user_id' : uid,
                           'limit' : 100,
                           'offset' : off_num,
                           })
        for f in friends:
            #print f["nick_name"]
            file_friend.write(f['nick_name'] + '\n')
        n = len(friends)
        off_num += n+1
    file_friend.close()


def GetTimeline(plurk):
    Posts = []
    offset = ''
    while len(Posts) < 100:
        plurks = plurk.callAPI('/APP/Timeline/getPlurks',{
            'offset' : offset,
            'limit' : 100
            })
        users = plurks["plurk_users"]

        if len(plurks["plurks"]) == 0:
            return Posts

        latestTime = {}
        for p in plurks["plurks"]:
            owner_id = p["owner_id"]
            user_info = users[str(owner_id)]

            if p.has_key('qualifier_translated'):
                qualifier = p['qualifier_translated']
            else:
                qualifier = p['qualifier']

            Time = ParseTime(p['posted'])

            Post = {}
            Post['content'] = qualifier +' : ' +  p['content']
            Post['id'] = str(p['plurk_id'])
            if user_info.has_key('nick_name'):
                Post['user_name'] = user_info['nick_name']
            else:
                Post['user_name'] = "no name"
            Post['time'] = Time
            Posts.append(Post)
            latestTime = Time
        Time = latestTime
        offset = '%d-%d-%dT%d:%d:%d' % (Time['year'], Time['month'], Time['day'], Time['hour'], Time['minute'], Time['second'])
    return Posts


def GetUserPlurks(plurk, user_id):
    Posts = []
    offset = ''

    while len(Posts) < 100:
        plurks = plurk.callAPI('/APP/Timeline/getPublicPlurks', {
                'user_id' : user_id,
                'limit'   : 200,
                'offset' : offset,
            })

        if len(plurks["plurks"]) == 0:
            return Posts
        users = plurks["plurk_users"]
        latestTime = {}
        for p in plurks["plurks"]:
            owner_id = p["owner_id"]
            user_info = users[str(owner_id)]
            
            if p.has_key('qualifier_translated'):
                qualifier = p['qualifier_translated']
            else:
                qualifier = p['qualifier']

            Time = ParseTime(p['posted'])

            Post = {}
            Post['content'] = qualifier +' : ' +  p['content']
            Post['id'] = str(p['plurk_id'])
            if user_info.has_key('nick_name'):
                Post['user_name'] = user_info['nick_name']
            else:
                Post['user_name'] = "no name"
            Post['time'] = Time
            Posts.append(Post)
            latestTime = Time
        Time = latestTime
        offset = '%d-%d-%dT%d:%d:%d' % (Time['year'], Time['month'], Time['day'], Time['hour'], Time['minute'], Time['second'])
    return Posts

        

def Reply(plurk, plurk_id , content):
    plurks = plurk.callAPI('/APP/Responses/responseAdd', {
        'plurk_id' : plurk_id,
        'content' : content.encode('utf-8'),
        'qualifier' : 'says'
        })

def Favorite(plurk ,plurk_id):
    text = plurk.callAPI('/APP/Timeline/favoritePlurks', {
        'ids' : [int(plurk_id)]
        })
    return text


def QueryMyTimeline(plurk, request):
    request = unicode(request, "utf-8")
    Posts = GetTimeline(plurk)
    new_Posts = []
    for p in Posts:
        if request in p['content']:
            new_Posts.append(p)
             
    return new_Posts


def QueryUserTimeline(plurk, user_id, request):
    request = unicode(request, "utf-8")
    Posts = GetUserPlurks(plurk, user_id)
    new_Posts = []
    for p in Posts:
        if request in p['content']:
            new_Posts.append(p)
             
    return new_Posts

    
def Query(plurk, request):
    plurks = plurk.callAPI('/APP/PlurkSearch/search',{
                           'query' : request})

    users = plurks["users"]
    Posts = []
    for p in plurks["plurks"]:
        owner_id = p["owner_id"]


        user_info = users[str(owner_id)]

        if p.has_key('qualifier_translated'):
            qualifier = p['qualifier_translated']
        else:
            qualifier = p['qualifier']
        
        #print ' ' + qualifier+ ' : '

        Time = ParseTime(p['posted'])
        
        Post = {}
        Post['content'] = qualifier +' : ' + p['content']
        Post['id'] = str(p['plurk_id'])
        if user_info.has_key('nick_name'):
            Post['user_name'] = user_info['nick_name']
        else:
            Post['user_name'] = "no name"
        Post['time'] = Time
        Posts.append(Post)
    return Posts
        

if __name__ == '__main__':
    try:
        opts, args = getopt.getopt(sys.argv[1:], "ho:v", ["help", "output="])
    except getopt.GetoptError, err:
        print str(err) # will print something like "option -a not recognized"
        usage()
        sys.exit(2)

    plurk = Plurk_Log()
    
    argc = len (sys.argv)

    if argc == 1:
        #do normal get time line
        Posts = GetTimeline(plurk)
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
                Posts = QueryUserTimeline(plurk, user, request)
            elif 'user' in locals():
                Posts = GetUserPlurks(plurk, user)
            elif 'request' in locals() and my:
                Posts = QueryMyTimeline(plurk, request)
            elif 'request' in locals() and not my:
                Posts = Query(plurk, request)
            elif my:
                Posts = GetTimeline(plurk)

            file2 = open('POST.json', 'w')
            output = json.dumps(Posts)
            file2.write(output)
            file2.close()
                
        elif cmp(sys.argv[1] , 'reply') == 0:
            plurk_id = sys.argv[2]
            file3 = open('reply', 'r')
            content = file3.read()
            file3.close()
            Reply(plurk, int(plurk_id), unicode(content,'utf8'))
        elif cmp(sys.argv[1], 'like') == 0:
            plurk_id = sys.argv[2]
            Favorite(plurk ,plurk_id)
        elif cmp(sys.argv[1], 'login') == 0:
            plurk = Plurk_Login(sys.argv[2])
            GetFriends(plurk)


  
    #content = '中文測試 OAuth API'
    #request = "good"
    #Posts = Query(plurk, request)
    #Posts = GetTimeline(plurk)

    #Posts = Query(plurk,request)


    #for p in Posts:
      #  print p['user_name']
       # print p['content'].encode('utf8')
	#print p['id']
        #print '\n'
    



    
