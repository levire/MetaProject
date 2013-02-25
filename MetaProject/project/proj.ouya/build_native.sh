APPNAME="HelloCpp"

# options

buildexternalsfromsource=
buildtests=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ code for $APPNAME using Android NDK

OPTIONS:
-s	Build externals from source
-t  Build tests
-h	this help
EOF
}

while getopts "sth" OPTION; do
case "$OPTION" in
s)
buildexternalsfromsource=1
;;
t)
buildtests=1
echo $*
shift
;;
h)
usage
exit 0
;;
esac
done

# paths

if [ -z "${NDK_ROOT+aaa}" ];then
echo "please define NDK_ROOT"
exit 1
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
# ... use paths relative to current directory
ROOT="$DIR/../.."
APP_ROOT="$DIR/.."
APP_OUYA_ROOT="$DIR"

echo "NDK_ROOT = $NDK_ROOT"
echo "ROOT = $ROOT"
echo "APP_ROOT = $APP_ROOT"
echo "APP_OUYA_ROOT = $APP_OUYA_ROOT"

# make sure assets is exist
if [ -d "$APP_OUYA_ROOT"/assets ]; then
    rm -rf "$APP_OUYA_ROOT"/assets
fi

mkdir "$APP_OUYA_ROOT"/assets

# copy resources
for file in "$APP_OUYA_ROOT"/Resources/*
do
if [ -d "$file" ]; then
    cp -rf "$file" "$APP_OUYA_ROOT"/assets
fi

if [ -f "$file" ]; then
    cp "$file" "$APP_OUYA_ROOT"/assets
fi
done

if [[ "$buildtests" ]]; then
    BUILD_TESTS="BUILD_TESTS=true"
else
    BUILD_TESTS="BUILD_TESTS=false"
fi

if [[ "$buildexternalsfromsource" ]]; then
    echo "Building external dependencies from source"
    set -x
    "$NDK_ROOT"/ndk-build -C "$APP_OUYA_ROOT" $* \
        "NDK_MODULE_PATH=${ROOT}:${ROOT}/cocos2dx/platform/third_party/android/source" \
        "${BUILD_TESTS}"
else
    echo "Using prebuilt externals"
    set -x
    "$NDK_ROOT"/ndk-build -B V=1 -C "$APP_OUYA_ROOT" $* \
        "NDK_MODULE_PATH=${ROOT}:${ROOT}/cocos2dx/platform/third_party/android/prebuilt" \
        "${BUILD_TESTS}"
fi
