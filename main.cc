#include <napi.h>

double calc(double a, double b)
{
    return a * b;
}

Napi::Number Calc(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    if (info.Length() < 2 || !info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    }

    Napi::Number first = info[0].As<Napi::Number>();
    Napi::Number second = info[1].As<Napi::Number>();

    double returnValue = calc(first.DoubleValue(), second.DoubleValue());

    return Napi::Number::New(env, returnValue);
}

void RunCallback(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    // Get arguments
    Napi::String first = info[0].As<Napi::String>();
    Napi::Function cb = info[1].As<Napi::Function>();
    Napi::Object obj = info[2].As<Napi::Object>();
    
    // Get object value
    Napi::Value val1 = obj.Get(first.Utf8Value());
    Napi::String val2 = val1.As<Napi::String>();

    // Create callback
    cb.Call(env.Global(), {Napi::String::New(env, val2.Utf8Value())});
}

Napi::Object init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "calc"), Napi::Function::New(env, Calc));
    exports.Set(Napi::String::New(env, "testCb"), Napi::Function::New(env, RunCallback));
    return exports;
};

NODE_API_MODULE(module_name, init);