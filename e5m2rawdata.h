#ifndef E5M2RAWDATA_H
#define E5M2RAWDATA_H
#include<QObject>
#include<gmp.h>
#include<bitset>
#include <QDebug>
//#include <QDecimal>

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
  bool m_sign;
  int32_t m_exp;
  std::bitset<8> m_mantiss;
  void updateRawData(){
    this->m_sign = (this->m_e5m2Raw >> 7 == 1);
    this->m_exp = (this->m_e5m2Raw << 1 >> 3) - 15;
    this->m_mantiss = (this->m_e5m2Raw << 6 >> 6);
    this->m_e5m2Hex = QString::asprintf("0x%x", m_e5m2Raw);
    this->m_u8Str = QString::asprintf("%u", m_e5m2Raw);
    this->m_s8Str = QString::asprintf("%d", m_e5m2Raw);
    this->m_e5m2Bits = QString::number(m_e5m2Raw,2);

    mpf_t r;
    mpf_t one;
    mpf_t two;
    mpf_init(r);
    mpf_init(one);
    mpf_init(two);
    mpf_set_d(r, 1.0);
    mpf_set_d(one, 1.0);
    mpf_set_d(two,2.0);
    for(int i = 1; i>= 0; i--){
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
    mp_exp_t p_point_pos;
    QString Qstr = mpf_get_str(nullptr, &p_point_pos, 10, 0, r);

    qDebug()  << p_point_pos;
    qDebug()  << Qstr;
    qDebug()  <<"\n";

    this->m_e5m2Str.clear();
    if(p_point_pos > 0){
     // int p = 0;

      //for(; p < p_point_pos; p++ ){

      this->m_e5m2Str.append(Qstr.left(p_point_pos));
     if(Qstr.length() > p_point_pos){
      this->m_e5m2Str.append('.');
      this->m_e5m2Str.append(Qstr.mid(p_point_pos));
      }
     if(Qstr.length() < p_point_pos){
        int num_of_zero = Qstr.length() - p_point_pos;
        for(int i = 0; i < num_of_zero; i++)
          this->m_e5m2Str.append('0');
      }
    }
    //if(p_point_pos == 0){
    //  this->m_e5m2Str.append(Qstr);
    //}
    //}

    if(p_point_pos <= 0){
      this->m_e5m2Str.append("0.");
      for(int i = 0; i < -p_point_pos;i++)
        this->m_e5m2Str.append('0');
      this->m_e5m2Str.append(Qstr);
    }


    //char str[100000];
    //gmp_snprintf(str,100000,"%.*Ff",r);
    //this->m_e5m2Str = QString::asprintf("%s",str);
  }
};

#endif // E5M2RAWDATA_H
