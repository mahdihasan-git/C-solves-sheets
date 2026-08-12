import math
 
# Accept the sliding angle in degrees
angle_deg = float(input("Enter angle (deg): "))
 
# Convert degrees to radians
angle_rad = math.radians(angle_deg)
 
# Coefficient of friction = tan(theta)
mu = math.tan(angle_rad)
 
print(f"Coefficient of friction, mu = {mu:.3f}")
