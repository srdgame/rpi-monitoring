#ifndef RAM_H
#define RAM_H

#define MB  (1024.0*1024.0)

class Ram
{
public:
    Ram();

    int getTotal(void);
    int getFree(void);
    int getLoad(void);
    int updateLoad(void);

private:
    int readInfo(void);
    int readTotal(void);

protected:
    double m_total;
    double m_load;
    double m_free;
};

#endif // RAM_H
