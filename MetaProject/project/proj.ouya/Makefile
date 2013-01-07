all:
	./build_native.sh
	pwd
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
	rm -rf ../../cocos2dx/platform/ouya/java/bin/*
	rm -rf ../../cocos2dx/platform/ouya/java/gen/

