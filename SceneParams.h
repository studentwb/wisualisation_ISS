#ifndef SCENEPARAMS_H
#define SCENEPARAMS_H

/*!
 * \brief SceneParams
 * Klasa odpowiada za ustawienia prametrow sceny, na ktorej rozkladane jest tlo
 */

class SceneParams {
  double  _AngleX_deg;


  double  _X_Light_deg = 0;
  double  _Y_Light_deg = 0;
  double  _Z_Light_deg = 0;

 public:

  SceneParams()
     { _AngleX_deg = 0; }

  void SetAngleX_deg(double AngleX_deg) { _AngleX_deg = AngleX_deg; }
  double GetAngleX_deg() const { return _AngleX_deg; }


  void SetZ_Light_deg(double Z_Light_deg) { _Z_Light_deg = Z_Light_deg; }
  double GetZ_Light_deg() const { return _Z_Light_deg; }

  void SetY_Light_deg(double Y_Light_deg) { _Y_Light_deg = Y_Light_deg; }
  double GetY_Light_deg() const { return _Y_Light_deg; }

  void SetX_Light_deg(double X_Light_deg) { _X_Light_deg = X_Light_deg; }
  double GetX_Light_deg() const { return _X_Light_deg; }

};


extern SceneParams  ScnParams;

#endif // SCENEPARAMS_H
