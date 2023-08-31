## Proxy Pattern (프록시 패턴)

일반적으로 프록시는 다른 무언가와 이어지는 인터페이스의 역할을 하는 클래스이다. 프록시는 어떠한 것(이를테면 네트워크 연결, 메모리 안의 커다란 객체, 파일, 또 복제할 수 없거나 수요가 많은 리소스)과도 인터페이스의 역할을 수행할 수 있다. (wiki)

프록시 패턴은 다양하게 사용된다.
1. 캐시 용도 : 인터넷에 프록시 서버를 설정하는 방법. 성능의 이점을 보기 위해 사용된다.
2. 로깅 용도 : 프록시 패턴을 사용해서 어떤 객체에 접근할 때, 로그를 계속 남긴다면 해당 객체를 어떻게 사용했는지 로그가 남을 것이다.
3. 보호 용도 : 사용자에 따라서 특정 객체를 사용가능한 범위를 설정하여 사용하도록 만들 수 있다. 예를 들면, 길드 객체를 길드원이 이용할 때와 길드장이 이용할 , 길드 객체를 이용할 수 있는지를 판단하여 결과를 내보낼 수 있다.
4. 지연 용도 : 사용하려는 객체가 엄청나게 무거운 객체이고 사용의 빈도가 낮다면, 지연의 용도로써 사용할 수 있다. 실제 사용 객체는 로드되지 않고 있다가 프록시 객체를 통해 실제 객체를 사용 시 할당을 하여 사용한다.

예를 들어보자. 회사 내에서 외부 인터넷을 사용할 때, 프록시 서버를 두어서 어떤 웹사이트를 검색했는지, 접근이 가능한 웹사이트인지, 그리고 웹 페이지를 캐싱하여 성능도 좋게 만들도록 하고 싶다. 

```c++

class IProxy {
    virtual bool canConnect(const string& ip) const {return true};
    virtual WebPage connect(const string& ip) {return WebPage(404, ip);}
    virtual void beforeConnect(const string& ip);
    virtual void afterConnect(const string& ip, const WebPage& page);
    virtual WebPage http(const string& ip);
}

class WebPage {
    WebPage(this._result, this._html);

    int     _result
    string  _html;
}

class ProxyServer : public IProxy {
    vector<IProxy*> _proxys;

    void addProxy(IProxy* proxy) {
        _proxys.push_back(proxy);
    }

    virtual bool canConnect(const string& ip) const {
        for(const auto* proxy : _proxys) {
            if(false == proxy->canConnect(ip)) {
                return false;
            }
        }
        return true;
    }

    virtual WebPage connect(const string& ip) 
    {
        if(!canConnect(ip)) {
            return false;
        }

        beforeConnect(ip);
        WebPage page(http(ip));
        afterConnect(ip, page);
        return page;
    };

    virtual WebPage http(const string& ip) {
        return WebPage(200, ip);
    }
}

// 로그 용도의 프록시
class LogginProxy : public IProxy {
    virtual void beforeConnect(const string& ip) {
        print("{ip} 페이지 fetch begin");
    }
    virtual void afterConnect(const string& ip, const WebPage& page) {
        print(page.ToString());
        print("{ip} 페이지 fetch end");
    }
}

// 보호 용도의 프록시
class ProtectProxy : public IProxy {
    hashset<string> blackList;
    virtual bool canConnect(const string& ip) const {
        return !blackList.find(ip);
    }

    virtual void afterConnect(const string& ip, const WebPage& page) {
        if(string.find(page.GetPage(), "욕욕")) {
            blackList.push_back(ip);
        }
    }
}

// 캐싱 용도의 프록시
class CachingProxy : public IProxy {
    hashmap<string, WebPage> cachePages;
    virtual WebPage http(const string& ip) {
        auto findIt = cachePages.find(ip);
        if(findIt.isValid()) {
            return findIt.second;
        }

        return super::http(ip);
    }


    virtual void afterConnect(const string& ip, const WebPage& page) {
        cachePages.insert(ip, page);
    }
}

void main() {
    ProxyServer proxyServer;
    proxyServer.addProxy(new LogginProxy());
    proxyServer.addProxy(new ProtectProxy());
    proxyServer.addProxy(new CachingProxy());
    ProxyServer.connect("naver.com");
    ProxyServer.connect("naver.com");
}


```

## 결론
실제 사용 객체를 곧바로 사용하지 않고, 특정 객체를 거쳐서 사용하는 것은 어댑터 패턴과 비슷한 것 같다. 하지만 용도 면에서는 차이가있다. 어댑터 패턴은 호환되지 않는 인터페이스를 가진 두 클래스를 함께 사용할 때 사용하거나 인터페이스를 편리하게 사용하기 위함이라면, 프록시 패턴은 캐시,로깅,보호 등의 용도로 사용한다. 어쨌든 클라이언트는 프록시 객체나 어댑터 객체를 사용할 때는 안에서 어떤 일이 일어나는지 알 필요가 없이 쉽게 사용하면서 여러 가지 기능을 사용하게 되는 건 같다. 
때