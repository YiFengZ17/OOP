#!/usr/bin/env bash
# 分发：bash pd.sh pdshow 20261105（先编译四个程序）
# 测试：bash pd.sh test（自动在临时目录编译并测试）
set -e
DIR="$(cd "$(dirname "$0")" && pwd)"
case "$1" in
    pdadd|pdlist|pdshow|pdremove)
        prog="$1"
        shift
        "$DIR/$prog" "$@"
        exit 0
        ;;
    test) ;;
    *)
        echo "Usage: bash pd.sh {pdadd|pdlist|pdshow|pdremove|test} [args...]" >&2
        exit 1
        ;;
esac

# 所有测试文件和程序都放在临时目录，不碰正式日记
TEST_DIR="$(mktemp -d)"
trap 'rm -rf "$TEST_DIR"' EXIT
for prog in pdadd pdlist pdshow pdremove; do
    g++ -std=c++17 -Wall -Wextra "$DIR/$prog.cpp" "$DIR/Date.cpp" "$DIR/Diary.cpp" -o "$TEST_DIR/$prog"
done
cp "$DIR/pd.sh" "$TEST_DIR/pd.sh"
cd "$TEST_DIR"

echo "1. 添加：点号结束和文件末尾结束"
printf 'Second day\n.\nIgnored line\n' > input.txt
bash pd.sh pdadd 20261106 < input.txt
printf 'First day\nSecond line\n' > input.txt
bash pd.sh pdadd 20261105 < input.txt
bash pd.sh pdshow 20261105 > actual.txt
diff input.txt actual.txt
printf 'Second day\n' > expected.txt
bash pd.sh pdshow 20261106 > actual.txt
diff expected.txt actual.txt

echo "2. 列表：日期排序和包含端点的范围"
bash pd.sh pdlist > actual.txt
printf '20261105\tFirst day\n20261106\tSecond day\n' > expected.txt
diff expected.txt actual.txt
bash pd.sh pdlist 20261105 20261106 > actual.txt
diff expected.txt actual.txt
bash pd.sh pdlist 20261106 20261106 > actual.txt
printf '20261106\tSecond day\n' > expected.txt
diff expected.txt actual.txt

echo "3. 同一天覆盖"
printf 'Updated content\n' > input.txt
bash pd.sh pdadd 20261105 < input.txt
bash pd.sh pdshow 20261105 > actual.txt
diff input.txt actual.txt

echo "4. 重定向协作：导出后添加到另一天"
bash pd.sh pdshow 20261105 > copy.txt
bash pd.sh pdadd 20261107 < copy.txt
bash pd.sh pdshow 20261107 > actual.txt
diff copy.txt actual.txt

echo "5. 删除成功，以及重复删除返回255"
bash pd.sh pdremove 20261107
if bash pd.sh pdremove 20261107; then
    echo "FAIL: repeated removal succeeded"
    exit 1
else
    test "$?" -eq 255
fi
bash pd.sh pdlist > actual.txt
printf '20261105\tUpdated content\n20261106\tSecond day\n' > expected.txt
diff expected.txt actual.txt

echo "6. 错误输入（下面的报错是预期结果）"
if bash pd.sh pdadd 20260230 < /dev/null; then exit 1; fi
if bash pd.sh pdshow; then exit 1; fi
if bash pd.sh pdlist 20261106 20261105; then exit 1; fi
echo "All tests passed."
