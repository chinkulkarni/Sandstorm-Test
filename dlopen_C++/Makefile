all: data-store shared-obj

data-store:
	g++ -Wl,--export-dynamic -o DataStore DataStore.cc -ldl

shared-obj:
	g++ -shared -fPIC -o UserProcedure.so UserProcedure.cc

clean:
	rm -f DataStore UserProcedure.so
