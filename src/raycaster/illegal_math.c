// HIGHLY UNSUBMITTABLE CODE

# include "Cub3d.h"

#define screenWidth 640
#define screenHeight 480
#define texWidth 64
#define texHeight 64

void illegal_math(void *parameter)
{
  t_raycaster	*raycaster = parameter;
  
//x and y start position
//   raycaster->player_pos.x = 8.5;
//   raycaster->player_pos.y = 1.5;
//initial direction vector //gotta figure out the 4 spawns
// raycaster->player_dir.x = 0.0;
// raycaster->player_dir.y = -1.0;
//the 2d raycaster version of camera plane
// raycaster->plane.x = 0.66
// raycaster->plane.y = 0.0;

  //start the main loop
int w = WINDOW_WIDTH;
int h = WINDOW_HEIGHT;
//   while(1)
//   {
    for(int x = 0; x < w; x++)
    {
      //calculate ray position and direction
      double cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
      double rayDirX = raycaster->player_dir.x + raycaster->plane.x*cameraX;
      double rayDirY = raycaster->player_dir.y + raycaster->plane.y*cameraX;

      //which box of the map we're in
      int mapX = (int)raycaster->player_pos.x;
      int mapY = (int)raycaster->player_pos.y;

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX); //turn into if statements
      double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY); //turn into if statements
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (raycaster->player_pos.x - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - raycaster->player_pos.x) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (raycaster->player_pos.y - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - raycaster->player_pos.y) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, either in x-direction, or in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        // if(worldMap[mapX][mapY] > 0) hit = 1;
        if(raycaster->map[mapY][mapX] == '1') hit = 1;
      }

      //Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
      if(side == 0) perpWallDist = (sideDistX - deltaDistX);
      else          perpWallDist = (sideDistY - deltaDistY);

      //Calculate height of line to draw on screen
      int lineHeight = (int)(h / perpWallDist);


      int pitch = 00; //figure out pitch

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + h / 2 + pitch;
      if(drawStart < 0) drawStart = 0;
      int drawEnd = lineHeight / 2 + h / 2 + pitch;
      if(drawEnd >= h) drawEnd = h - 1;

int y = 0;
while (y < drawStart)
{
	mlx_put_pixel(raycaster->screen, x, y, raycaster->col_ce);
	y++;
}

y = WINDOW_HEIGHT - 1;
while (y > drawEnd)
{
	mlx_put_pixel(raycaster->screen, x, y, raycaster->col_fl);
	y--;
}

/* (until ceiling/floor)
      //texturing calculations
    //   int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!
      int texNum = 0;

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(side == 0) wallX = raycaster->player_pos.y + perpWallDist * rayDirY;
      else          wallX = raycaster->player_pos.x + perpWallDist * rayDirX;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * (double)texWidth);
      if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * texHeight / lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - pitch - h / 2 + lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        int texY = (int)texPos & (texHeight - 1);
        texPos += step;
        // Uint32 color = texture[texNum][texHeight * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(side == 1) color = (color >> 1) & 8355711;
        buffer[y][x] = color;
      }
	*/
    }

    // drawBuffer(buffer[0]);
    // for(int y = 0; y < h; y++) for(int x = 0; x < w; x++) buffer[y][x] = 0; //clear the buffer instead of cls()
    //timing for input and FPS counter
    // oldTime = time;
    // time = getTicks();
    // double frameTime = (time - oldTime) / 1000.0; //frametime is the time this frame has taken, in seconds
    // print(1.0 / frameTime); //FPS counter
    // redraw();

    // //speed modifiers
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

    // readKeys();
    // //move forward if no wall in front of you
    // if(keyDown(SDLK_UP))
    // {
    //   if(worldMap[int(raycaster->player_pos.x + raycaster->player_dir.x * moveSpeed)][int(raycaster->player_pos.y)] == false) raycaster->player_pos.x += raycaster->player_dir.x * moveSpeed;
    //   if(worldMap[int(raycaster->player_pos.x)][int(raycaster->player_pos.y + raycaster->player_dir.y * moveSpeed)] == false) raycaster->player_pos.y += raycaster->player_dir.y * moveSpeed;
    // }
    // //move backwards if no wall behind you
    // if(keyDown(SDLK_DOWN))
    // {
    //   if(worldMap[int(raycaster->player_pos.x - raycaster->player_dir.x * moveSpeed)][int(raycaster->player_pos.y)] == false) raycaster->player_pos.x -= raycaster->player_dir.x * moveSpeed;
    //   if(worldMap[int(raycaster->player_pos.x)][int(raycaster->player_pos.y - raycaster->player_dir.y * moveSpeed)] == false) raycaster->player_pos.y -= raycaster->player_dir.y * moveSpeed;
    // }
    // //rotate to the right
    // if(keyDown(SDLK_RIGHT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = raycaster->player_dir.x;
    //   raycaster->player_dir.x = raycaster->player_dir.x * cos(-rotSpeed) - raycaster->player_dir.y * sin(-rotSpeed);
    //   raycaster->player_dir.y = oldDirX * sin(-rotSpeed) + raycaster->player_dir.y * cos(-rotSpeed);
    //   double oldPlaneX = raycaster->plane.x;
    //   raycaster->plane.x = raycaster->plane.x * cos(-rotSpeed) - raycaster->plane.y * sin(-rotSpeed);
    //   raycaster->plane.y = oldPlaneX * sin(-rotSpeed) + raycaster->plane.y * cos(-rotSpeed);
    // }
    // //rotate to the left
    // if(keyDown(SDLK_LEFT))
    // {
    //   //both camera direction and camera plane must be rotated
    //   double oldDirX = raycaster->player_dir.x;
    //   raycaster->player_dir.x = raycaster->player_dir.x * cos(rotSpeed) - raycaster->player_dir.y * sin(rotSpeed);
    //   raycaster->player_dir.y = oldDirX * sin(rotSpeed) + raycaster->player_dir.y * cos(rotSpeed);
    //   double oldPlaneX = raycaster->plane.x;
    //   raycaster->plane.x = raycaster->plane.x * cos(rotSpeed) - raycaster->plane.y * sin(rotSpeed);
    //   raycaster->plane.y = oldPlaneX * sin(rotSpeed) + raycaster->plane.y * cos(rotSpeed);
    // }
    // if(keyDown(SDLK_ESCAPE))
    // {
    //   break;
    // }
//   }
	mlx_image_to_window(raycaster->mlx, raycaster->screen, 0, 0);

}
