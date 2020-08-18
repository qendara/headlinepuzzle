HEADERS= \
	headline.h \
	solver.h \
	common.h \
	menu.h \
	alphabet.h

INCLUDES= \
	headline.cpp \
	solver.cpp \
	alphabet.cpp \
	common.cpp \
	menu.cpp \
	main.cpp

fives: create_five_letter_list.cpp common.h common.cpp
	g++ -o fives common.cpp create_five_letter_list.cpp -I.

patterns: create_patterns.cpp common.h common.cpp
	g++ -o patterns common.cpp create_patterns.cpp -I.

orders: create_orders.cpp common.h common.cpp
	g++ -o orders common.cpp create_orders.cpp -I.

scores: create_pair_scores.cpp common.h common.cpp
	g++ -o pair_scores common.cpp create_pair_scores.cpp -I.

test: $(HEADERS) $(INCLUDES)
	g++ -o test $(INCLUDES) -I. -g
