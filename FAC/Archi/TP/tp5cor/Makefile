# Options utiles a la compilation
CFLAGS = -g -Wall -Wextra -std=c99

SRCS = associativeCacheSimulation.c directCacheSimulation.c testAssociativeCache.c testDirectCache.c associativeCache.c directCache.c bits.c

# Par defaut, on fait tout
all:	testDirectCache directCacheSimulation testAssociativeCache associativeCacheSimulation

# Edition de liens des divers programmes
testDirectCache: testDirectCache.o directCache.o bits.o
	@echo "Building $@"
	cc $(CFLAGS) -o testDirectCache testDirectCache.o directCache.o bits.o

directCacheSimulation: directCacheSimulation.o directCache.o bits.o
	@echo "Building $@"
	cc $(CFLAGS) -o directCacheSimulation directCacheSimulation.o directCache.o bits.o

testAssociativeCache: testAssociativeCache.o associativeCache.o directCache.o bits.o
	@echo "Building $@"
	cc $(CFLAGS) -o testAssociativeCache testAssociativeCache.o associativeCache.o directCache.o bits.o

associativeCacheSimulation: associativeCacheSimulation.o associativeCache.o directCache.o bits.o
	@echo "Building $@"
	cc $(CFLAGS) -o associativeCacheSimulation associativeCacheSimulation.o associativeCache.o directCache.o bits.o

.c.o :
	@echo "Building $@"
	cc $(CFLAGS) -o $@ -c $<

# Pour indiquer les dependances non implicites
testDirectCache.o: directCache.h

directCacheSimulation.o: directCache.h

directCache.o: bits.h

associativeCache.o: directCache.h

associativeCacheSimulation.o: associativeCache.h

testAssociativeCache.o: associativeCache.h

# Utile pour y voir clair
clean:
	rm -f *.o testDirectCache directCacheSimulation testAssociativeCache associativeCacheSimulation
