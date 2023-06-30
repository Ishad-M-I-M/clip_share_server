#!/bin/bash

. init.sh

files=(
    "file 1.txt"
    "file_2.txt"
    "sub/file 3.txt"
    "sub/file 4.txt"
    "sub 1/file 5.txt"
    "sub 1/subsub/file 6.txt"
    "sub 1/subsub/file_7.txt"
    "sub 1/subsub_2/file_8.txt"
)

mkdir -p original && cd original

for f in "${files[@]}"; do
    if [[ "$f" = */* ]]; then
        mkdir -p "${f%/*}";
    fi;
    echo "${f}"$'\n'"abc" > "${f}"
done

chunks=""

appendToChunks () {
    fname="$1"
    if [ -d "${fname}" ]; then
        for f in "${fname}"/*; do
            appendToChunks "${f}"
        done
    elif [ -f "${fname}" ]; then
        nameLength=$(printf "%016x" $(printf "${fname}" | wc -c))
        fileSize=$(printf "%016x" $(stat -c '%s' "${fname}"))
        content=$(cat "${fname}" | xxd -p | tr -d '\n')
        chunks+="${nameLength}$(printf "${fname}" | xxd -p)${fileSize}${content}"
    fi
}

for f in *; do
    appendToChunks "${f}"
done

cd ..
mkdir -p copies
mv clipshare.conf copies/
cd copies

# restart the server in new directory
"../../../$1" -r &> /dev/null

# remove the conf file
rm -f clipshare.conf

proto=$(printf "\x02" | xxd -p)
method=$(printf "\x04" | xxd -p)
fileCount=$(printf "%016x" $(printf "${#files[@]}"))

responseDump=$(printf "${proto}${method}${fileCount}${chunks}" | xxd -r -p | client_tool | xxd -p | tr -d '\n')

protoAck=$(printf "\x01" | xxd -p)
methodAck=$(printf "\x01" | xxd -p)

expected="${protoAck}${methodAck}"

if [ "${responseDump}" != "${expected}" ]; then
    showStatus fail "Incorrect response."
    exit 1
fi

cd ..

diffOutput=$(diff -rq original copies 2>&1)
if [ ! -z "${diffOutput}" ]; then
    showStatus "fail" "Files do not match."
    exit 1
fi

showStatus pass