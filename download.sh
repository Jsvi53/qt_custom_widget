#!/bin/bash
# 配置远程设备信息
REMOTE_USER="root"
REMOTE_IP="192.168.7.1"
REMOTE_PATH="~/"

# 要传输的文件路径
LOCAL_FILE="build/arm_debug/qt_custom_widget"

# 传输文件到远程设备
echo "正在将文件传输到远程设备..."
scp "$LOCAL_FILE" "${REMOTE_USER}@${REMOTE_IP}:${REMOTE_PATH}"

if [ $? -ne 0 ]; then
    echo "文件传输失败，请检查网络连接或文件路径是否正确。"
    exit 1
fi

echo "文件传输成功！"
ssh ${REMOTE_USER}@${REMOTE_IP}


