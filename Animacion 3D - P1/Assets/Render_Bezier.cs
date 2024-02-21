using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Render_Bezier : MonoBehaviour
{
    public Transform point0, point1, point2, point3;
    public int numPoints = 50;
    public Transform sphere;

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

                // Create a new sphere at the position
                Instantiate(sphere, pos, Quaternion.identity).tag = "Sphere";
            }
        }
    }
}
