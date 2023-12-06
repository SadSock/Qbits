#ifndef E4M3RAWDATA_H
#define E4M3RAWDATA_H

#include<QObject>
#include<gmp.h>
#include<bitset>
#include <QDebug>

class E4m3RawData : public QObject
{
  Q_OBJECT

  Q_PROPERTY(uint8_t m_e4m3Raw READ gete4m3Raw WRITE sete4m3Raw NOTIFY e4m3RawChanged)
  Q_PROPERTY(QString m_u8Str READ getu8Str WRITE setu8Str NOTIFY u8StrChanged)
  Q_PROPERTY(QString m_s8Str READ gets8Str WRITE sets8Str NOTIFY s8StrChanged)
  Q_PROPERTY(QString m_e4m3Str READ gete4m3Str WRITE sete4m3Str NOTIFY e4m3StrChanged)
  Q_PROPERTY(QString m_e4m3Hex READ gete4m3Hex WRITE sete4m3Hex NOTIFY e4m3HexChanged)
public:
  explicit E4m3RawData(QObject *parent = nullptr)
      :m_e4m3Raw(0),m_u8Str("0"),m_s8Str("0"),m_e4m3Str("0"),m_e4m3Hex("0.0")
  {}
  ~E4m3RawData(){}

 Q_INVOKABLE bool gete4m3BitsbyIdx(size_t idx){
   if( ((1ULL << idx) & this->m_e4m3Raw) )
    return true;
   else
    return false;
 }

void sete4m3Raw(const uint8_t& e4m3Raw){
   this->m_e4m3Raw = e4m3Raw;
   emit e4m3RawChanged(m_e4m3Raw);
}

uint8_t gete4m3Raw() const {return m_e4m3Raw;}

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

void sete4m3Str(const QString& e4m3Str){
  this->m_e4m3Str = e4m3Str;
  emit e4m3StrChanged(m_e4m3Str);
}

QString gete4m3Str() const {return m_e4m3Str;}

void sete4m3Hex(const QString& e4m3Hex){
  this->m_e4m3Hex = e4m3Hex;
  emit e4m3HexChanged(m_e4m3Hex);
}

QString gete4m3Hex() const {return m_e4m3Hex;}

void sete4m3Bits(const QString& e4m3Bits){
  this->m_e4m3Bits = e4m3Bits;
  emit e4m3HexChanged(m_e4m3Bits);
}

QString gete4m3Bits() const {return m_e4m3Bits;}

signals:
  void updateUi(QString &m_u8Str, QString &m_s8Str, QString &m_e4m3Str);
  void e4m3RawChanged(uint8_t e4m3Raw);
  void u8StrChanged(QString &u8Str);
  void s8StrChanged(QString &s8Str);
  void e4m3StrChanged(QString &e4m3Str);
  void e4m3HexChanged(QString &e4m3Hex);
  void e4m3BitsChanged(QString &e4m3Bits);


public slots:

  void sete4m3RawbyBit(bool predictor, size_t idx){
    if(predictor){
      uint8_t mask = 1ULL << idx;
    m_e4m3Raw = m_e4m3Raw | mask;
    }else{
      uint8_t mask = ~(1ULL << idx);
    m_e4m3Raw = m_e4m3Raw & mask;
    }
    updateRawData();
    emit updateUi(m_u8Str,m_s8Str,m_e4m3Str);
  }

  void sete4m3RawbyU8Str(const QString &u8Str){

    this->m_e4m3Raw = u8Str.toULongLong();
    updateRawData();
    emit updateUi(m_u8Str,m_s8Str,m_e4m3Str);
  }

  void sete4m3RawbyS8Str(const QString &s8Str){

    int8_t tmp = s8Str.toLongLong();
    this->m_e4m3Raw = *(uint8_t*)&tmp;
    updateRawData();
    emit updateUi(m_u8Str,m_s8Str,m_e4m3Str);
  }

private:
  uint8_t m_e4m3Raw;
  QString m_u8Str;
  QString m_s8Str;
  QString m_e4m3Str;
  QString m_e4m3Hex;
  QString m_e4m3Bits;
  bool m_sign;
  int32_t m_exp;
  std::bitset<8> m_mantiss;
  void updateRawData(){
    this->m_sign = (this->m_e4m3Raw >> 7 == 1);
    this->m_exp = ((uint8_t)(this->m_e4m3Raw << (uint8_t)1) >> 4) - 7;
    qDebug()  <<"exp"<<this->m_exp;
    this->m_mantiss = ((uint8_t)(this->m_e4m3Raw << 5) >> 5);
    this->m_e4m3Hex = QString::asprintf("0x%x", m_e4m3Raw);
    this->m_u8Str = QString::asprintf("%u", m_e4m3Raw);
    this->m_s8Str = QString::asprintf("%d", m_e4m3Raw);
    this->m_e4m3Bits = QString::number(m_e4m3Raw,2);

    mpf_t r;
    mpf_t one;
    mpf_t two;
    mpf_init(r);
    mpf_init(one);
    mpf_init(two);
    mpf_set_d(r, 1.0);
    mpf_set_d(one, 1.0);
    mpf_set_d(two,2.0);
    for(int i = 2; i>= 0; i--){
        mpf_div(one,one,two);
        if(m_mantiss[i]){
          mpf_add(r,r,one);
        }
    }
    if(this->m_exp >=0){
        mpf_mul_2exp(r, r, this->m_exp);}
    else{
        mpf_div_2exp(r,r,-this->m_exp);
    }

    this->m_e4m3Str.clear();
    mp_exp_t p_point_pos;
    QString Qstr = mpf_get_str(nullptr, &p_point_pos, 10, 0, r);
    int p_point_num = Qstr.length() - p_point_pos;

    char p_r_str[10000];
    gmp_snprintf(p_r_str,10000, "%.*Ff", p_point_num, r);

    qDebug()  <<"exp"<<this->m_exp;
    qDebug()  <<"mantiss"<<this->m_mantiss.to_string();

    if(this->m_sign)
      this->m_e4m3Str.append('-');
    this->m_e4m3Str.append(p_r_str);
  }
};



#endif // E4M3RAWDATA_H
