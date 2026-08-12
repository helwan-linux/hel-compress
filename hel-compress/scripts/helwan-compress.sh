#!/bin/bash
# سكربت لتسهيل التشغيل

CMD=$1
INPUT=$2
OUTPUT=$3
shift 3

./hel-compress "$CMD" "$INPUT" "$OUTPUT" "$@"
