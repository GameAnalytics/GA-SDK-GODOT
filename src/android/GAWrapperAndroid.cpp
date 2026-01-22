#include "GAWrapperAndroid.h"
#include <android/log.h>

namespace gameanalytics 
{
        constexpr const char* LOG_TAG = "GameAnalytics";
        constexpr const char* GAMEANALYTICS_CLASS_NAME = "com/gameanalytics/sdk/GameAnalytics";

        static JavaVM* javaVM             = nullptr;
        static jobject gameActivity       = nullptr;
        static jclass  gameAnalyticsClass = nullptr;

        struct ScopedJni
        {
            ScopedJni() = default;

            ~ScopedJni()
            {
                if(env && javaVM)
                {
                    javaVM->DetachCurrentThread();
                    env = nullptr;
                }
            }

            JNIEnv* Get()
            {
                if(!env)
                {
                    Attach();
                }

                return env;
            }

            JNIEnv* operator->()
            {
                return Get();
            }

            private:

                bool Attach()
                {
                    if(!javaVM)
                    {
                        return false;
                    }

                    return javaVM->AttachCurrentThread(&env, nullptr) == JNI_OK;
                }

                JNIEnv* env = nullptr;
        };

        static thread_local ScopedJni jniEnv;

        static FPSTracker androidFPSTracker;

        GAWrapperAndroid::GAWrapperAndroid():
            GAWrapper()
        {
        }

        GAWrapperAndroid::~GAWrapperAndroid()
        {
        }

        JNIEnv* GAWrapperAndroid::GetJavaEnv()
        {
            return jniEnv.Get();
        }

        jclass GAWrapperAndroid::GetGameAnalyticsClass()
        {
            return jniEnv->FindClass(GAMEANALYTICS_CLASS_NAME);
        }

        std::string GAWrapperAndroid::ConvertJString(jstring s)
        {
            JNIEnv* env = GetJavaEnv();
            if(env && s)
            {
                const char* cstr   = env->GetStringUTFChars(s, 0);
                std::string result = cstr;
                env->ReleaseStringUTFChars(s, cstr);
                return result;
            }
            else
            {
                return "";
            }
        }

        void GAWrapperAndroid::SetAvailableCustomDimensions01(const std::vector<std::string>& list)
        {
            constexpr const char* methodName = "configureAvailableCustomDimensions01";

            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "([Ljava/lang/String;)V");

                if (jMethod)
                {
                    jstring str;
                    jsize len = list.size();
                    jobjectArray j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string const& s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetAvailableCustomDimensions02(const std::vector<std::string>& list)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "configureAvailableCustomDimensions02";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string const& s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetAvailableCustomDimensions03(const std::vector<std::string>& list)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "configureAvailableCustomDimensions03";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string const& s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetAvailableResourceCurrencies(const std::vector<std::string>& list)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "configureAvailableResourceCurrencies";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string const& s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetAvailableResourceItemTypes(const std::vector<std::string>& list)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();

            constexpr const char* methodName = "configureAvailableResourceItemTypes";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "([Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring str;
                    jobjectArray j_array = 0;
                    jsize len = list.size();
                    j_array = env->NewObjectArray(len, env->FindClass("java/lang/String"), 0);

                    int i = 0;
                    for (std::string const& s : list)
                    {
                        str = env->NewStringUTF(s.c_str());
                        env->SetObjectArrayElement(j_array, i, str);
                        ++i;
                    }

                    env->CallStaticVoidMethod(jClass, jMethod, j_array);
                    for (i = 0; i < list.size(); ++i)
                    {
                        jobject localRef = env->GetObjectArrayElement(j_array, i);
                        env->DeleteLocalRef(localRef);
                    }
                    env->DeleteLocalRef(j_array);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetBuild(std::string const& build)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "configureBuild";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(build.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetAutoDetectAppVersion(bool flag)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            const char* methodName = "configureAutoDetectAppVersion";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        std::string GAWrapperAndroid::CallStringMethod(std::string const& name)
        {
            constexpr const char* signature = "()Ljava/lang/String;";

            std::string result = "";

            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();

            if(env && jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, name.c_str(), signature);
                if(jMethod)
                {
                    jstring jString = (jstring)env->CallStaticObjectMethod(jClass, jMethod);
                    result = ConvertJString(jString);
                    env->DeleteLocalRef(jString);
                }

                env->DeleteLocalRef(jClass);
            }

            return result;
        }

        std::string GAWrapperAndroid::GetUserId()
        {
            return CallStringMethod("getUserId");
        }

        std::string GAWrapperAndroid::GetExternalUserId()
        {
            return CallStringMethod("getExternalUserId");
        }

        void GAWrapperAndroid::SetCustomUserId(std::string const& userId)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "configureUserId";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(userId.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::UseRandomizedId(bool)
        {
            // random id is used by default
        }

        void GAWrapperAndroid::SetExternalUserId(std::string const& userId)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "configureExternalUserId";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(userId.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetSDKVersion(std::string const& gameEngineSdkVersion)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "configureSdkGameEngineVersion";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(gameEngineSdkVersion.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetGameEngineVersion(std::string const& gameEngineSdkVersion)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "configureGameEngineVersion";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_string = env->NewStringUTF(gameEngineSdkVersion.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_string);
                    env->DeleteLocalRef(j_string);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::Initialize(std::string const& gameKey, std::string const& gameSecret)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "initialize";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;)V");

                if(jMethod)
                {
                    jobject activity = gameanalytics::gameActivity;
                    jstring j_gameKey = env->NewStringUTF(gameKey.c_str());
                    jstring j_gameSecret = env->NewStringUTF(gameSecret.c_str());
                    
                    env->CallStaticVoidMethod(jClass, jMethod, activity, j_gameKey, j_gameSecret);
                    
                    env->DeleteLocalRef(j_gameKey);
                    env->DeleteLocalRef(j_gameSecret);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddBusinessEvent(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const&cartType, std::string const& receipt, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addBusinessEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_currency = env->NewStringUTF(currency.c_str());
                    jstring j_itemType = env->NewStringUTF(itemType.c_str());
                    jstring j_itemId = env->NewStringUTF(itemId.c_str());
                    jstring j_cartType = env->NewStringUTF(cartType.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_currency, amount, j_itemType, j_itemId, j_cartType, j_fields, mergeFields);
                    env->DeleteLocalRef(j_currency);
                    env->DeleteLocalRef(j_itemType);
                    env->DeleteLocalRef(j_itemId);
                    env->DeleteLocalRef(j_cartType);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddBusinessEventWithReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType,
                                             std::string const& receipt, std::string const& store, std::string const& signature, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addBusinessEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_currency = env->NewStringUTF(currency.c_str());
                    jstring j_itemType = env->NewStringUTF(itemType.c_str());
                    jstring j_itemId = env->NewStringUTF(itemId.c_str());
                    jstring j_cartType = env->NewStringUTF(cartType.c_str());
                    jstring j_receipt = env->NewStringUTF(receipt.c_str());
                    jstring j_store = env->NewStringUTF(store.c_str());
                    jstring j_signature = env->NewStringUTF(signature.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_currency, amount, j_itemType, j_itemId, j_cartType, j_receipt, j_store, j_signature, j_fields, mergeFields);
                    env->DeleteLocalRef(j_currency);
                    env->DeleteLocalRef(j_itemType);
                    env->DeleteLocalRef(j_itemId);
                    env->DeleteLocalRef(j_cartType);
                    env->DeleteLocalRef(j_receipt);
                    env->DeleteLocalRef(j_store);
                    env->DeleteLocalRef(j_signature);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddBusinessEventAndAutoFetchReceipt(std::string const& currency, int amount, std::string const& itemType, std::string const& itemId, std::string const& cartType, std::string const& fields, bool mergeFields)
        {
            __android_log_print(ANDROID_LOG_WARN, LOG_TAG, "Cannot auto fetch the receipt, sending regular business event...");
            return AddBusinessEvent(currency, amount, itemType, itemId, cartType, "", fields, mergeFields);
        }

        void GAWrapperAndroid::AddResourceEvent(EGAResourceFlowType flowType, std::string const& currency, float amount, std::string const& itemType, std::string const& itemId, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addResourceEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(ILjava/lang/String;FLjava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_currency = env->NewStringUTF(currency.c_str());
                    jstring j_itemType = env->NewStringUTF(itemType.c_str());
                    jstring j_itemId = env->NewStringUTF(itemId.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, static_cast<int>(flowType), j_currency, amount, j_itemType, j_itemId, j_fields, mergeFields);
                    env->DeleteLocalRef(j_currency);
                    env->DeleteLocalRef(j_itemType);
                    env->DeleteLocalRef(j_itemId);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddProgressionEvent(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addProgressionEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_progression01 = env->NewStringUTF(progression01.c_str());
                    jstring j_progression02 = env->NewStringUTF(progression02.c_str());
                    jstring j_progression03 = env->NewStringUTF(progression03.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, static_cast<int>(progressionStatus), j_progression01, j_progression02, j_progression03, j_fields, mergeFields);
                    env->DeleteLocalRef(j_progression01);
                    env->DeleteLocalRef(j_progression02);
                    env->DeleteLocalRef(j_progression03);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddProgressionEventWithScore(EGAProgressionStatus progressionStatus, std::string const& progression01, std::string const& progression02, std::string const& progression03, int score, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addProgressionEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;DLjava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_progression01 = env->NewStringUTF(progression01.c_str());
                    jstring j_progression02 = env->NewStringUTF(progression02.c_str());
                    jstring j_progression03 = env->NewStringUTF(progression03.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, static_cast<int>(progressionStatus), j_progression01, j_progression02, j_progression03, (double)score, j_fields, mergeFields);
                    env->DeleteLocalRef(j_progression01);
                    env->DeleteLocalRef(j_progression02);
                    env->DeleteLocalRef(j_progression03);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddDesignEvent(std::string const& eventId, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            const char* methodName = "addDesignEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;Ljava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_eventId = env->NewStringUTF(eventId.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_eventId, j_fields, mergeFields);
                    env->DeleteLocalRef(j_eventId);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddDesignEventWithValue(std::string const& eventId, float value, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addDesignEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;DLjava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_eventId = env->NewStringUTF(eventId.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_eventId, value, j_fields, mergeFields);
                    env->DeleteLocalRef(j_eventId);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddErrorEvent(EGAErrorSeverity severity, std::string const& message, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addErrorEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(ILjava/lang/String;Ljava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_message = env->NewStringUTF(message.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, static_cast<int>(severity), j_message, j_fields, mergeFields);
                    env->DeleteLocalRef(j_message);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddAdEvent(EGAAdAction action, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addAdEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_adSdkName = env->NewStringUTF(adSdkName.c_str());
                    jstring j_adPlacement = env->NewStringUTF(adPlacement.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, static_cast<int>(action), static_cast<int>(adType), j_adSdkName, j_adPlacement, j_fields, mergeFields);
                    env->DeleteLocalRef(j_adSdkName);
                    env->DeleteLocalRef(j_adPlacement);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddAdEventWithDuration(EGAAdAction action, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, int64_t duration, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addAdEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(IILjava/lang/String;Ljava/lang/String;JLjava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_adSdkName = env->NewStringUTF(adSdkName.c_str());
                    jstring j_adPlacement = env->NewStringUTF(adPlacement.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, static_cast<int>(action), static_cast<int>(adType), j_adSdkName, j_adPlacement, duration, j_fields, mergeFields);
                    env->DeleteLocalRef(j_adSdkName);
                    env->DeleteLocalRef(j_adPlacement);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::AddAdEventWithReason(EGAAdAction action, EGAAdType adType, std::string const& adSdkName, std::string const& adPlacement, EGAAdError noAdReason, std::string const& fields, bool mergeFields)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "addAdEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(IILjava/lang/String;Ljava/lang/String;ILjava/lang/String;Z)V");

                if(jMethod)
                {
                    jstring j_adSdkName = env->NewStringUTF(adSdkName.c_str());
                    jstring j_adPlacement = env->NewStringUTF(adPlacement.c_str());
                    jstring j_fields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, static_cast<int>(action), static_cast<int>(adType), j_adSdkName, j_adPlacement, noAdReason, j_fields, mergeFields);
                    env->DeleteLocalRef(j_adSdkName);
                    env->DeleteLocalRef(j_adPlacement);
                    env->DeleteLocalRef(j_fields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetInfoLog(bool flag)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "setEnabledInfoLog";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetVerboseLog(bool flag)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "setEnabledVerboseLog";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetEnabledManualSessionHandling(bool flag)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "setEnabledManualSessionHandling";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetEnabledErrorReporting(bool flag)
        {
            JNIEnv *env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char *methodName = "setEnabledErrorReporting";

            if (jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if (jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetEnabledEventSubmission(bool flag, bool doCacheLocally)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "setEnabledEventSubmission";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(ZZ)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, flag, doCacheLocally);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetGlobalCustomEventFields(std::string const& fields)
        {
            constexpr const char* methodName = "setGlobalCustomEventFields";

            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();

            if(env && jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring jfields = env->NewStringUTF(fields.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, jfields);
                    env->DeleteLocalRef(jfields);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }
                
                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetCustomDimension01(std::string const& customDimension)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "setCustomDimension01";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_customDimension = env->NewStringUTF(customDimension.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_customDimension);
                    env->DeleteLocalRef(j_customDimension);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetCustomDimension02(std::string const& customDimension)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "setCustomDimension02";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_customDimension = env->NewStringUTF(customDimension.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_customDimension);
                    env->DeleteLocalRef(j_customDimension);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::SetCustomDimension03(std::string const& customDimension)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "setCustomDimension03";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;)V");

                if(jMethod)
                {
                    jstring j_customDimension = env->NewStringUTF(customDimension.c_str());
                    env->CallStaticVoidMethod(jClass, jMethod, j_customDimension);
                    env->DeleteLocalRef(j_customDimension);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::StartSession()
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "startSession";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "()V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::EndSession()
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "endSession";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "()V");
                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        double GAWrapperAndroid::GetRemoteConfigsValueAsNumber(std::string const& key, double defaultValue) {
            return defaultValue;
        }

        std::string GAWrapperAndroid::GetRemoteConfigsValueAsJson(std::string const& key) {
            return "";
        }

        std::string GAWrapperAndroid::GetRemoteConfigsValueAsString(std::string const& key, std::string const& defaultValue)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "getRemoteConfigsValueAsString";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_key = env->NewStringUTF(key.c_str());
                    jstring j_defaultValue = env->NewStringUTF(defaultValue.c_str());
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod, j_key, j_defaultValue);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                    env->DeleteLocalRef(j_key);
                    env->DeleteLocalRef(j_defaultValue);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            return result;
        }

        bool GAWrapperAndroid::IsRemoteConfigsReady()
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "isRemoteConfigsReady";
            bool result = false;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "()Z");

                if(jMethod)
                {
                    result = env->CallStaticBooleanMethod(jClass, jMethod);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            return result;
        }

        std::string GAWrapperAndroid::GetRemoteConfigsContentAsString()
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "getRemoteConfigsContentAsString";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "()Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            return result;
        }

        std::string GAWrapperAndroid::GetABTestingId()
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "getABTestingId";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "()Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            return result;
        }

        std::string GAWrapperAndroid::GetABTestingVariantId()
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();

            constexpr const char* methodName = "getABTestingVariantId";
            std::string result;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "()Ljava/lang/String;");

                if(jMethod)
                {
                    jstring j_s = (jstring)env->CallStaticObjectMethod(jClass, jMethod);
                    const char* s = env->GetStringUTFChars(j_s, 0);
                    result = s;
                    env->ReleaseStringUTFChars(j_s, s);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            return result;
        }

        void GAWrapperAndroid::EnableSDKInitEvent(bool value)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "enableSDKInitEvent";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, value);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::EnableFpsHistogram(FPSTracker tracker, bool value)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();

            constexpr const char* methodName = "enableFpsHistogram";
            constexpr const char* methodNameCustomTracker = "setCustomFPSTracker";

            androidFPSTracker = tracker;

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                jmethodID jTrackerMethod = env->GetStaticMethodID(jClass, methodNameCustomTracker, "(Lcom/gameanalytics/sdk/health/IFpsTracker;)V");
                jclass nativeFPSTrackerClass = env->FindClass("com/gameanalytics/sdk/health/NativeFpsTracker");

                jmethodID ctor = env->GetMethodID(nativeFPSTrackerClass, "<init>", "()V");
                jobject javaTracker = env->NewObject(nativeFPSTrackerClass, ctor);

                if(jMethod && jTrackerMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, value);
                    if(value)
                    {
                        env->CallStaticVoidMethod(jClass, jTrackerMethod, javaTracker);
                    }
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::EnableMemoryHistogram(bool value)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "enableMemoryHistogram";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, value);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::EnableHealthHardwareInfo(bool value)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "enableHealthHardwareInfo";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, value);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::EnableAdvertisingId(bool value)
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "setGAIDTracking";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "(Z)V");

                if(jMethod)
                {
                    env->CallStaticVoidMethod(jClass, jMethod, value);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }
        }

        void GAWrapperAndroid::OnQuit()
        {
            return;
        }

        void GAWrapperAndroid::SetWritablePath(std::string const& path)
        {
            (void)path;
        }

        int64_t GAWrapperAndroid::GetElapsedSessionTime() 
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "getElapsedSessionTime";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "()L");

                if(jMethod)
                {
                    jlong value = env->CallStaticLongMethod(jClass, jMethod);
                    return static_cast<int64_t>(value);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            return 0;
        }   

        int64_t GAWrapperAndroid::GetElapsedTimeForPreviousSession()
        {
            //TODO: implement when GA android sdk supports it
            return 0;
        }
        
        int64_t GAWrapperAndroid::GetElapsedTimeFromAllSessions() 
        {
            JNIEnv* env = GetJavaEnv();
            jclass jClass = GetGameAnalyticsClass();
            constexpr const char* methodName = "getElapsedTotalSessionTime";

            if(jClass)
            {
                jmethodID jMethod = env->GetStaticMethodID(jClass, methodName, "()L");

                if(jMethod)
                {
                    jlong value = env->CallStaticLongMethod(jClass, jMethod);
                    return static_cast<int64_t>(value);
                }
                else
                {
                    __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find method %s ***", methodName);
                }

                env->DeleteLocalRef(jClass);
            }
            else
            {
                __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "*** Failed to find class %s ***", GAMEANALYTICS_CLASS_NAME);
            }

            return 0;
        }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_gameanalytics_godotgameanalytics_GodotGameAnalytics_setActivityNative(JNIEnv *env, jobject _this, jobject activity)
{
    __android_log_print(ANDROID_LOG_DEBUG, gameanalytics::LOG_TAG, "GameAnalytics: set activity");
    gameanalytics::gameActivity = env->NewGlobalRef(activity);
}

extern "C"
JNIEXPORT jfloat JNICALL
Java_com_gameanalytics_sdk_health_NativeFpsTracker_getFPSNative(JNIEnv *env, jobject _this) 
{
    return gameanalytics::androidFPSTracker();
}

extern "C"
JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void*)
{
    __android_log_print(ANDROID_LOG_DEBUG, gameanalytics::LOG_TAG, "GameAnalytics.so has been loaded");
    gameanalytics::javaVM = vm;

    return JNI_VERSION_1_6;
}