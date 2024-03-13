using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/*
 *  Script que divide la pantalla en dos para mostrar dos cámaras diferentes
 *  que simulan la visión de un ojo izquierdo y un ojo derecho.
 */
public class Dividir_Camaras : MonoBehaviour
{
    public Camera ojo_izquierdo;
    public Camera ojo_derecho;

    // Start is called before the first frame update
    void Start()
    {
        ojo_izquierdo.rect = new Rect(0, 0, 0.5f, 1);
        ojo_derecho.rect = new Rect(0.5f, 0, 0.5f, 1);        
    }

    // Update is called once per frame
    void Update()
    {
        ojo_izquierdo.rect = new Rect(0, 0, 0.5f, 1);
        ojo_derecho.rect = new Rect(0.5f, 0, 0.5f, 1);
    }
}
