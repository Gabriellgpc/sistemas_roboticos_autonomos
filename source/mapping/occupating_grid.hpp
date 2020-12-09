#pragma once
#include <configSpaceTools.hpp> //Vector2D, Config
#include <vector>

constexpr double l_0 = 0.0;//iniciar ocupados
constexpr double l_oc= 0.5;//incremento em log odd para celulas provavelmente ocupadas
constexpr double l_L =-0.5;//incremento para log odd para celulas provavelmente nao ocupadas

double log_odd(const double &p);
double inv_log_odd(const double &l);

class ProximitySensorInfo
{
public:
    ProximitySensorInfo(const float &min_range, 
                        const float &max_range, 
                        const float &opening,
                        const float &angle, 
                        const float &e = 0);
    ~ProximitySensorInfo();

    //atualize measure_dist com um valor negativo para indicar que não ha dados de medição
    void updateMeasure(const float& measure_dist, const Vector2D & measure_point);
    
    //retorna um valor negativo caso não tenha dados de medições
    inline float zt()const{ return sensor_measure_dist; }
    inline float get_measure_dist()const{ return sensor_measure_dist; }
    inline Vector2D get_measure_point()const{ return sensor_measure_point; }
    inline float get_error()const{ return error; }
    inline float e()const{ return error; }
    inline float get_opening_angle()const{ return opening_angle; }
    inline float ang_range()const{ return opening_angle; }
    inline float max()const{ return range[1]; }
    inline float min()const{ return range[0]; }
    inline float get_ori()const{ return theta; }
    inline float ori()const{ return theta; }

    inline Vector2D &point(){ return sensor_measure_point; }
private:
    /** Propriedades do sensor **/
    //erro na distancia
    float error;
    //angulo de abertura
    float opening_angle; 
    //[min, max]
    float range[2];
    //orientação do sensor com relação à orientação do robo
    float theta;

    /** Dados da medição **/
    //distancia ate o ponto mais proximo
    float sensor_measure_dist;
    //ponto no plano x,y do mundo / localização do ponto detectado
    Vector2D sensor_measure_point;
};

class CellGrid
{
public:
    Vector2D pos;
    double l;
    double p;
};

class OccupationGrid
{
public:
    //grade com width e height composta de celulas quadradas com size_cell de lado
    OccupationGrid(const float &width, const float &height, const float& size_cell = 0.1);
    ~OccupationGrid();
    
    void update(const ProximitySensorInfo& sensor, const Config & q);
    inline std::vector<CellGrid> get_OG()const { return map; }
private:
    std::vector<CellGrid> map;

    //modelo inverso simples de um sensor de proximidade
    double _inverse_model(const CellGrid &mi, const ProximitySensorInfo &z, const Config& q);
};