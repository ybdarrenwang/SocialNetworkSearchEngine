GplusplusFlag = -Wall
objects = main.o SocialNet.o User.o Message.o Photo.o PlurkPuDecorator.o PlurkReplyDecorator.o TwitterReplyDecorator.o TwitterTweetDecorator.o json.o Plurk.o Twitter.o AutoCompleteBasicQ.o AutoCompleteAdvQ.o

all: $(objects)
	g++ $(GplusplusFlag) -o SocialNetworkSearchEngine $^

%.o: %.cpp
	g++ -c -o $@ $<

.PHONY : clean
clean :
	rm $(objects)
