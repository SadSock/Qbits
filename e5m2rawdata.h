#ifndef E5M2RAWDATA_H
#define E5M2RAWDATA_H
#include<QObject>
#include <QDecimal>

class E5m2RawData : public QObject
{
  Q_OBJECT

  Q_PROPERTY(uint8_t m_e5m2Raw READ gete5m2Raw WRITE sete5m2Raw NOTIFY e5m2RawChanged)
  Q_PROPERTY(QString m_u8Str READ getu8Str WRITE setu8Str NOTIFY u8StrChanged)
  Q_PROPERTY(QString m_s8Str READ gets8Str WRITE sets8Str NOTIFY s8StrChanged)
  Q_PROPERTY(QString m_e5m2Str READ gete5m2Str WRITE sete5m2Str NOTIFY e5m2StrChanged)
  Q_PROPERTY(QString m_e5m2Hex READ gete5m2Hex WRITE sete5m2Hex NOTIFY e5m2HexChanged)
public:
  explicit E5m2RawData(QObject *parent = nullptr)
      :m_e5m2Raw(0),m_u8Str("0"),m_s8Str("0"),m_e5m2Str("0"),m_e5m2Hex("0.0")
  {}
  ~E5m2RawData(){}

 Q_INVOKABLE bool gete5m2BitsbyIdx(size_t idx){
   if( ((1ULL << idx) & this->m_e5m2Raw) )
    return true;
   else
    return false;
 }

void sete5m2Raw(const uint8_t& e5m2Raw){
   this->m_e5m2Raw = e5m2Raw;
   emit e5m2RawChanged(m_e5m2Raw);
}

uint8_t gete5m2Raw() const {return m_e5m2Raw;}

void setu8Str(const QString& u8Str){
  this->m_u8Str = u8Str;
  emit u8StrChanged(m_u8Str);
}

QString getu8Str() const {return m_u8Str;}

void sets8Str(const QString& s8Str){
  this->m_s8Str = s8Str;
  emit s8StrChanged(m_s8Str);
}

QString gets8Str() const {return m_s8Str;}

void sete5m2Str(const QString& e5m2Str){
  this->m_e5m2Str = e5m2Str;
  emit e5m2StrChanged(m_e5m2Str);
}

QString gete5m2Str() const {return m_e5m2Str;}

void sete5m2Hex(const QString& e5m2Hex){
  this->m_e5m2Hex = e5m2Hex;
  emit e5m2HexChanged(m_e5m2Hex);
}

QString gete5m2Hex() const {return m_e5m2Hex;}

void sete5m2Bits(const QString& e5m2Bits){
  this->m_e5m2Bits = e5m2Bits;
  emit e5m2HexChanged(m_e5m2Bits);
}

QString gete5m2Bits() const {return m_e5m2Bits;}

signals:
  void updateUi(QString &m_u8Str, QString &m_s8Str, QString &m_e5m2Str);
  void e5m2RawChanged(uint8_t e5m2Raw);
  void u8StrChanged(QString &u8Str);
  void s8StrChanged(QString &s8Str);
  void e5m2StrChanged(QString &e5m2Str);
  void e5m2HexChanged(QString &e5m2Hex);
  void e5m2BitsChanged(QString &e5m2Bits);


public slots:

  void sete5m2RawbyBit(bool predictor, size_t idx){
    if(predictor){
      uint8_t mask = 1ULL << idx;
    m_e5m2Raw = m_e5m2Raw | mask;
    }else{
      uint8_t mask = ~(1ULL << idx);
    m_e5m2Raw = m_e5m2Raw & mask;
    }
    updateRawData();
    emit updateUi(m_u8Str,m_s8Str,m_e5m2Str);
  }

  void sete5m2RawbyU8Str(const QString &u8Str){

    this->m_e5m2Raw = u8Str.toULongLong();
    updateRawData();
    emit updateUi(m_u8Str,m_s8Str,m_e5m2Str);
  }

  void sete5m2RawbyS8Str(const QString &s8Str){

    int8_t tmp = s8Str.toLongLong();
    this->m_e5m2Raw = *(uint8_t*)&tmp;
    updateRawData();
    emit updateUi(m_u8Str,m_s8Str,m_e5m2Str);
  }

private:
  uint8_t m_e5m2Raw;
  QString m_u8Str;
  QString m_s8Str;
  QString m_e5m2Str;
  QString m_e5m2Hex;
  QString m_e5m2Bits;
  void updateRawData(){
    this->m_e5m2Hex = QString::asprintf("0x%x", m_e5m2Raw);
    this->m_u8Str = QString::asprintf("%u", m_e5m2Raw);
    this->m_s8Str = QString::asprintf("%d", m_e5m2Raw);
    //this->m_e5m2Str = QString::asprintf("%lf", *(double*)&m_e5m2Raw);
    this->m_e5m2Bits = QString::number(m_e5m2Raw,2);



  }
};

#endif // E5M2RAWDATA_H
