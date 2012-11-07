GPP = g++
GPPFlag = -O2 -Wall

SRC = src
BUILD = build
DOC = doc
DOXYGEN = doxygen
DOXYGENCFG = $(DOC)/doxygen.cfg

CDIR = cd
MKDIR = mkdir -p
<<<<<<< HEAD
RM = rm -f
=======
RM = rm
>>>>>>> 3d8b7065426dd341feadb29b1c55bdec8c1b120c

objects = $(BUILD)/main.o $(BUILD)/SocialNet.o $(BUILD)/User.o $(BUILD)/Message.o $(BUILD)/Photo.o $(BUILD)/PlurkPuDecorator.o $(BUILD)/PlurkReplyDecorator.o $(BUILD)/TwitterReplyDecorator.o $(BUILD)/TwitterTweetDecorator.o $(BUILD)/json.o $(BUILD)/Plurk.o $(BUILD)/Twitter.o $(BUILD)/AutoCompleteBasicQ.o $(BUILD)/AutoCompleteAdvQ.o

all: $(objects)
	$(GPP) $(GPPFlag) -o SocialNetworkSearchEngine.exe $^

$(BUILD)/%.o: $(SRC)/%.cpp
	$(GPP) -c -o $@ $<

.PHONY : doc
doc:
	$(CDIR) $(DOC);
	$(DOXYGEN) $(DOXYGENCFG)

.PHONY : clean
clean:
	$(RM) $(BUILD)/*
