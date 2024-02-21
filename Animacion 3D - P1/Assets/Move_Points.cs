using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Move_Points : MonoBehaviour
{
    // Void OnDrag is called when the user drags the point
    // Start is called before the first frame update

    private void OnMouseDrag()
    {
        // Get the mouse position
        Vector3 posAct = Input.mousePosition;

        float posX = Input.mousePosition.x + Input.GetAxis("Mouse X") * Time.deltaTime; 
        float posY = Input.mousePosition.y + Input.GetAxis("Mouse Y") * Time.deltaTime;

        // Set the position of the point to the world position
        transform.position = new Vector3(-posX, posY, posAct.z);
    }


    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
