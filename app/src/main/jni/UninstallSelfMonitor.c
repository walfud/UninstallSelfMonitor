
#include "UninstallSelfMonitor.h"
#include <android/log.h>
#include <unistd.h>
#include <stdio.h>

static jboolean sIsCopy = JNI_TRUE;

#define NEW_STRING_UTF(str)             (*jniEnv)->NewStringUTF(jniEnv, str)
#define GET_STRING_UTF_CHARS(str)       (*jniEnv)->GetStringUTFChars(jniEnv, str, &sIsCopy)

//#define LOG_X(level, tag, msg)  __android_log_write(level, \
//                            (*jniEnv)->GetStringUTFChars(jniEnv, (*jniEnv)->NewStringUTF(jniEnv, tag), &sIsCopy), \
//                            (*jniEnv)->GetStringUTFChars(jniEnv, (*jniEnv)->NewStringUTF(jniEnv, msg), &sIsCopy))

const static char *TAG = "From libUninstallSelfMonitor.so";
#define LOG_D(tag, ...)  __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)
#define LOG_E(tag, ...)  __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)


const static char *s_pkgName = "/data/data/com.walfud.uninstallselfmonitor";


JNIEXPORT void JNICALL Java_com_walfud_uninstallselfmonitor_Native_init(JNIEnv *jniEnv, jclass jClass)
{
    // 初始化 log
    LOG_D(TAG, "start");

    pid_t pid = fork();
    if (pid < 0)
    {
        // 创建卸载监控进程失败
        LOG_E(TAG, "`fork`failed");

        return;
    }
    else if (pid > 0)
    {
        // 父进程
        LOG_D(TAG, "monitor process id: %d", pid);
    }
    else
    {
        // 新创建的子进程
        // 执行监控
        while (1)
        {
            FILE *pFile = fopen(s_pkgName, "r");
            if (pFile != NULL)
            {
                // 正常
                fclose(pFile);

                LOG_D(TAG, ".");

                sleep(1);
            }
            else
            {
                // 检测到 '被卸载'
//                execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d", "http://shouji.360.cn/web/uninstall/uninstall.html", (char *)NULL);
				execlp("am", "am", "start", "--user", "0", "-a","android.intent.action.VIEW", "-d","http://www.baidu.com", NULL);

                LOG_D(TAG, "fire!");

                break;
            }

        }
    }

    // 结束监听
    LOG_D(TAG, "end");
}