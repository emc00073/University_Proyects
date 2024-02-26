using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move_Points : MonoBehaviour
{
    // Void OnDrag is called when the user drags the point
    // Start is called before the first frame update

    private void OnMouseDrag()
    {
        /*
        // Script to move the points fixing the z position to 0
        Vector3 mousePos = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 20);
        Vector3 objPos = Camera.main.ScreenToWorldPoint(mousePos);
        transform.position = objPos;
        */

        // Script to move the points in the x and y axis
        Vector3 mousePos = new Vector3(Input.mousePosition.x, Input.mousePosition.y, 20);
        Vector3 objPos = Camera.main.ScreenToWorldPoint(mousePos);
        transform.position = objPos;
    }


    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
