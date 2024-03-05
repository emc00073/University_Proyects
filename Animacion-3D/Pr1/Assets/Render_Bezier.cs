using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Render_Bezier : MonoBehaviour
{
    public Transform point0, point1, point2, point3, slider;
    public int numPoints = 50;
    public Transform sphere;
    public bool renderSphereLines = true;

    public float V0 = 0.2f;
    public float Ta = 0.4f;
    public float Tda = 0.8f;
    public float d = 0.0f;
    
    
    // Add a button to start an animation to move the cube along the path
    public void StartAnimation()
    {
        StartCoroutine(MoveCube());
    }

    // Coroutine to move the cube along the path with fade in and fade out animation
    IEnumerator MoveCube()
    {
        Time time = new Time();
        float t = 0;

        while (d < 1)
        {
            t += Time.deltaTime;

            if (d < Ta) {
                // Acceleration
                d = V0 * (t * t) / (2.0f * Ta);
            }else if(d < Tda) {
                // Constant speed
                d = (V0 * Ta / 2.0f) + (V0 * (t - Ta));
            }
            else {
                // Deceleration
                d = (V0 * Ta / 2.0f) + (V0 * (Tda - Ta)) + (V0 - ((V0 * (t - Tda)) / (1 - Tda)) / 2) * (t - Tda);
            }

            float x = Mathf.Pow(1 - d, 3) * point0.position.x +
                      3 * Mathf.Pow(1 - d, 2) * d * point1.position.x +
                      3 * (1 - d) * Mathf.Pow(d, 2) * point2.position.x +
                      Mathf.Pow(d, 3) * point3.position.x;
            float y = Mathf.Pow(1 - d, 3) * point0.position.y +
                      3 * Mathf.Pow(1 - d, 2) * d * point1.position.y +
                      3 * (1 - d) * Mathf.Pow(d, 2) * point2.position.y +
                      Mathf.Pow(d, 3) * point3.position.y;
            float z = Mathf.Pow(1 - d, 3) * point0.position.z + 
                      3 * Mathf.Pow(1 - d, 2) * d * point1.position.z + 
                      3 * (1 - d) * Mathf.Pow(d, 2) * point2.position.z + 
                      Mathf.Pow(d, 3) * point3.position.z;

            slider.position = new Vector3(x, y, z);
            yield return null;
        }
    }

    // Start is called before the first frame update
    void Start()
    {
        // Draw the line with numPoints spheres
        for (float t = 0; t <= 1; t += 1.0f / numPoints)
        {
            Vector3 pos = Mathf.Pow(1 - t, 3) * point0.position +
                          3 * Mathf.Pow(1 - t, 2) * t * point1.position +
                          3 * (1 - t) * Mathf.Pow(t, 2) * point2.position +
                          Mathf.Pow(t, 3) * point3.position;
            
            // Create a new sphere at the position with tag: Sphere
            Instantiate(sphere, pos, Quaternion.identity).tag = "Sphere";
        }        
        StartAnimation();
    }

    // Update is called once per frame
    void Update()
    {
        // Check if the points have changed
        if (point0.hasChanged || point1.hasChanged || point2.hasChanged || point3.hasChanged)
        {
            // Clear the scene
            GameObject[] spheres = GameObject.FindGameObjectsWithTag("Sphere");
            foreach (GameObject sphere in spheres)
            {
                Destroy(sphere);
            }

            // Draw the line with numPoints spheres
            for (float t = 0; t <= 1; t += 1.0f / numPoints)
            {
                Vector3 pos = Mathf.Pow(1 - t, 3) * point0.position +
                              3 * Mathf.Pow(1 - t, 2) * t * point1.position +
                              3 * (1 - t) * Mathf.Pow(t, 2) * point2.position +
                              Mathf.Pow(t, 3) * point3.position;

                // Create a new sphere at the position and render it if renderSphereLines is true
                if (renderSphereLines)
                {
                    Instantiate(sphere, pos, Quaternion.identity).tag = "Sphere";
                }
            }
        }
    }
}
