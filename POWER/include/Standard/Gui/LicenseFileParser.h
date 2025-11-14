#pragma once

#include <QString>
#include <memory>
#include <QDateTime>

namespace standard {
// 产品授权信息结构体
struct ProductLicenseInfo {
    QString name;
    QString version;
    QString type;
    QString expiration_date;
    QVector<QString> features;
};

// 完整授权信息结构体
struct FullLicenseInfo {
    QString version;
    QString id;
    QString device_id;
    QString issuer;
    QString issued_date;
    QString issued_to;
    QString mode;
    QVector<ProductLicenseInfo> products;
    bool is_valid;
    QString verification_message;
};

class LicenseFileParser {

public:

    static LicenseFileParser& GetInstance();
    LicenseFileParser(const LicenseFileParser&) = delete;
    LicenseFileParser& operator=(const LicenseFileParser&) = delete;

    ~LicenseFileParser();

    // 加载并解析license文件
    bool LoadLicenseFile(const QString& filePath);
    
    // 获取完整授权信息
    const FullLicenseInfo& GetFullLicenseInfo() const;
    
    // 检查是否需要显示到期提醒(30天内)
    bool NeedExpirationReminder(const QString& productName) const;
    
    // 获取距离到期的天数
    int GetDaysToExpiration(const QString& productName) const;

private:

    LicenseFileParser();
    // 解析JSON格式的license内容
    bool ParseLicenseContent(const QString& content);
    
    // 字符串转日期
    bool StringToDate(const QString& dateStr, QDate& outDate) const;
    
    // 计算两个日期之间的天数差
    int DaysBetweenDates(const QDate& start, const QDate& end) const;

    FullLicenseInfo m_license_info;
};

}  // namespace standard
