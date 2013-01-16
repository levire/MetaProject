all:
	./build_native.sh
	ant -Dsdk.dir=$(ADK_ROOT) debug

run:
	adb -d uninstall org.cocos2dx.hellocpp
	adb -d install bin/HelloWorld-debug.apk
	adb -d logcat | grep cocos2d

clean:
	rm -rf libs/
	rm -rf obj/
	rm -rf bin/*
	rm -rf gen/
	rm -rf assets/*

ccclean:
	rm -rf ../../../cocos2dx/platform/android/java/bin/*
	rm -rf ../../../cocos2dx/platform/android/java/gen/

tests:
	./build_native.sh -t
	ant -Dsdk.dir=$(ADK_ROOT) debug