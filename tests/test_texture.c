
//uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];

#define W 800
#define H 800

// index = (y * image->width + x) * BPP

#include "../MLX42/include/MLX42/MLX42.h"

int	ft_rgba_to_int(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void fill_baseimg(mlx_image_t *main, int color)
{
	for (int i = 0; i < W; ++i) {
		for (int j = 0; j < H; ++j)
		{
			if (j >= 100 && j <= 600)
				mlx_put_pixel(main, i, j, color);
			else
				mlx_put_pixel(main, i, j, 255);
		}
	}
}

void try_texture(mlx_image_t *main, mlx_image_t *texture)
{
	for (int y = 0; y < H; y++) {
		for (int x = 0; x < W; x++) {
			int m_index = (y * main->width + x) * 4;

			int tx = x % texture->width;
			int ty = (y - 100) % texture->height;
			int t_index = (ty * texture->width + tx) * 4;

			if (main->pixels[m_index] == 255 && main->pixels[m_index + 1] == 165 && main->pixels[m_index + 2] == 0) {
				main->pixels[m_index] = texture->pixels[t_index];
				main->pixels[m_index + 1] = texture->pixels[t_index + 1];
				main->pixels[m_index + 2] = texture->pixels[t_index + 2];
			}
		}
	}

}

int main(void)
{
	mlx_t *mlx = mlx_init(W, H, "test", false);
	mlx_image_t *main = mlx_new_image(mlx, W, H);

	xpm_t	*texture = mlx_load_xpm42("grid-neon.xpm42");
	mlx_image_t *wall = mlx_texture_to_image(mlx, &(texture->texture));

	if (mlx->width != wall->width)
		mlx_resize_image(wall, 250, 250);

	fill_baseimg(main, ft_rgba_to_int(255, 165, 0, 255));
	//try_texture(main, wall);

	mlx_image_to_window(mlx, main, 0, 0);


	mlx_loop(mlx);
	mlx_terminate(mlx);
	return 0;
}

//cc test_texture.c ../MLX42/build/libmlx42.a -I "./MLX42/include/" -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"