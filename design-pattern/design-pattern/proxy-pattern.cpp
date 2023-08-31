#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>


using namespace std;

class WebPage {
public:
    WebPage(const int result, const string& ip, const string& html)
        : _ip(ip)
        , _result(result)
        , _html(html) {}

    int     _result;
    string  _ip;
    string  _html;
};

WebPage InvalidPage = WebPage(404, string(), string());

class IProxy {
public:
    virtual bool canConnect(const string& ip) const { return true; };
    virtual WebPage connect(const string& ip) { return InvalidPage; }
    virtual void beforeConnect(const string& ip) {}
    virtual void afterConnect(const string& ip, const WebPage& page) {}
    virtual WebPage http(const string& ip) { return InvalidPage; }
};


class ProxyServer : public IProxy {
    vector<IProxy*> _proxys;
public:
    void addProxy(IProxy* proxy) {
        _proxys.push_back(proxy);
    }
    virtual bool canConnect(const string& ip) const {
        for (const auto* proxy : _proxys) {
            if (false == proxy->canConnect(ip)) {
                return false;
            }
        }
        return true;
    }

    virtual void beforeConnect(const string& ip) {
        for (auto* proxy : _proxys) {
            proxy->beforeConnect(ip);
        }
    }
    virtual void afterConnect(const string& ip, const WebPage& page) {
        for (auto* proxy : _proxys) {
            proxy->afterConnect(ip, page);
        }
    }
    virtual WebPage connect(const string& ip)
    {
        if (!canConnect(ip)) {
            return InvalidPage;
        }

        beforeConnect(ip);
        WebPage page(http(ip));
        afterConnect(ip, page);
        return page;
    };

private:
    virtual WebPage http(const string& ip) {
        return WebPage(200, ip, string("").append(ip).append("�� ������ ����~~~"));
    }
};

// �α� �뵵�� ���Ͻ�
class LogginProxy : public IProxy {
    virtual void beforeConnect(const string& ip) {
        cout << "====== " << ip << "������ fetch begin" << endl;
    }
    virtual void afterConnect(const string& ip, const WebPage& page) {
        cout << page._html << endl;
        cout << "====== " << ip << "������ fetch end" << endl;
    }
};

// ��ȣ �뵵�� ���Ͻ�
class ProtectProxy : public IProxy {
    unordered_set<string> blackList;
    virtual bool canConnect(const string& ip) const {
        if (blackList.end() == blackList.find(ip)) {
            cout << "������Ʈ�� ���ԵǾ ���� �Ұ� " << endl;
            return false;
        }
        return true;
    }

    virtual void afterConnect(const string& ip, const WebPage& page) {
        if (std::string::npos != page._html.find("��")) {
            blackList.insert(ip);
        }
    }   
};

// ĳ�� �뵵�� ���Ͻ�
class CachingProxy : public IProxy {
    unordered_map<string, WebPage> cachePages;
    virtual WebPage http(const string& ip) {
        auto findIt = cachePages.find(ip);
        if (cachePages.end() != findIt) {
            cout << "ĳ�� ����" << endl;
            return findIt->second;
        }

        return __super::http(ip);
    }


    virtual void afterConnect(const string& ip, const WebPage& page) {
        cachePages.insert( make_pair(ip, page));
    }
};
 
void main() {
    ProxyServer proxyServer;
    proxyServer.addProxy(new LogginProxy());
    proxyServer.addProxy(new ProtectProxy());
    proxyServer.addProxy(new CachingProxy());

    while (true) {
        std::string input;
        std::getline(std::cin, input);
        proxyServer.connect(input);
    }
}
