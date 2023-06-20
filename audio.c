/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barramacmahon <barramacmahon@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:50:14 by barramacmah       #+#    #+#             */
/*   Updated: 2023/05/30 17:54:45 by barramacmah      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifdef __APPLE__
    #define MA_NO_RUNTIME_LINKING
#endif

#define MINIAUDIO_IMPLEMENTATION
#include "cub3d.h"

int ft_audio(t_cub *cub)
{
    ma_result result;
    ma_engine engine;
    
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        return result;
    }

    ma_engine_play_sound(&engine, "Apollo Down.wav", NULL);
    // result = ma_sound_init_from_file(&engine, "/Users/barramacmahon/Code/42/cub3d/cube3d/Apollo Down.wav", 0, NULL, NULL, &cub->sound);
    // printf("YO\n");
    // if (result != MA_SUCCESS) {
    //     return result;
    // }
    // ma_sound_set_volume(&cub->sound, 1);
    // ma_sound_start(&cub->sound);
    // ma_sound_set_looping(&sound, 1);
    // ma_sound_start(&vars.sound.track2);
    return 0;
}