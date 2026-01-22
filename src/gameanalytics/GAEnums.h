#pragma once

enum class EGAResourceFlowType : int
{
    undefined = 0,
    source = 1,
    sink = 2
};

enum class EGAProgressionStatus : int
{
    undefined = 0,
    start = 1,
    complete = 2,
    fail = 3
};

enum class EGAErrorSeverity : int
{
    undefined = 0,
    debug = 1,
    info = 2,
    warning = 3,
    error = 4,
    critical = 5
};

enum class EGAAdAction : int
{
    undefined = 0,
    clicked = 1,
    show = 2,
    failedshow = 3,
    rewardreceived = 4,
    request = 5,
    loaded = 6
};

enum class EGAAdType : int
{
    undefined = 0,
    video = 1,
    rewardedvideo = 2,
    playable = 3,
    interstitial = 4,
    offerwall = 5,
    banner = 6
};

enum class EGAAdError : int
{
    undefined = 0,
    unknown = 1,
    offline = 2,
    nofill = 3,
    internalerror = 4,
    invalidrequest = 5,
    unabletoprecache = 6
};

enum class EGAValueType : int
{
    value_number = 0,
    value_string,
    value_bool
};
