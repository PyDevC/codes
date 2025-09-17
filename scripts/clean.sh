#!/usr/bin/env bash

if [[ -z $CODES ]]; then
    echo "Set CODES environment variable"
    exit 0
fi

pushd "$CODES"
outs=$(find . | grep a.out)
if [[ -z $outs ]]; then
    exit 0
fi

echo $outs
for out in $outs; do
    rm -rf $out
done

popd
