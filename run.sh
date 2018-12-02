function assertEqual() {
    [[ "$1" == "$2" ]] && echo "Equal" || echo "Expected $1, Got $2"
}

#make clean
#make makebin.exe

"
./makebin.exe zaki.txt zaki.data
./getconf.exe -i zaki -o zaki
./exttpose.exe -i zaki -o zaki -p 1 -l -x -s 0.3
./spade.exe -i zaki -s 0.3 -Z 10 -z 10 -u 1 -r -e 1 -o


makebin_actual=`md5sum zaki.data | cut -d' ' -f1`
makebin_correct=`md5sum correct/zaki.data | cut -d' ' -f1`
assertEqual $makebin_actual $makebin_correct

getconf_actual=`md5sum zaki.conf | cut -d' ' -f1`
getconf_correct=`md5sum correct/zaki.conf | cut -d' ' -f1`
assertEqual $getconf_actual $getconf_correct

exttpose_actual=`md5sum zaki.idx | cut -d' ' -f1`
exttpose_correct=`md5sum correct/zaki.idx | cut -d' ' -f1`
assertEqual $exttpose_actual $exttpose_correct

exttpose_actual=`md5sum zaki.tpose | cut -d' ' -f1`
exttpose_correct=`md5sum correct/zaki.tpose | cut -d' ' -f1`
assertEqual $exttpose_actual $exttpose_correct
"

./main.exe exttpose
makebin_actual=`md5sum zaki.data | cut -d' ' -f1`
makebin_correct=`md5sum correct/zaki.data | cut -d' ' -f1`
assertEqual $makebin_actual $makebin_correct

getconf_actual=`md5sum zaki.conf | cut -d' ' -f1`
getconf_correct=`md5sum correct/zaki.conf | cut -d' ' -f1`
assertEqual $getconf_actual $getconf_correct

exttpose_actual=`md5sum zaki.idx | cut -d' ' -f1`
exttpose_correct=`md5sum correct/zaki.idx | cut -d' ' -f1`
assertEqual $exttpose_actual $exttpose_correct

"
exttpose_actual=`md5sum zaki.tpose | cut -d' ' -f1`
exttpose_correct=`md5sum correct/zaki.tpose | cut -d' ' -f1`
assertEqual $exttpose_actual $exttpose_correct

./main.exe spade
"