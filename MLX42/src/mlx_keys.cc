/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx_keys.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: W2Wizard <main@w2wizard.dev>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/01 21:06:45 by W2Wizard      #+#    #+#                 */
/*   Updated: 2023/02/13 12:24:40 by W2Wizard      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42_Int.hh"

//= Private =//

static void mlx_key_callback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
{
	const t_mlx* mlx = glfwGetWindowUserPointer(window);
	const mlx_key_t key_hook = ((mlx_ctx_t*)mlx->context)->key_hook;
	const t_mlx_key_data callback_data = {
		key,
		action,
		scancode,
		mods,
	};

	key_hook.func(callback_data, key_hook.param);
}

//= Public =//

void mlx_key_hook(t_mlx* mlx, t_mlx_keyfunc func, void* param)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(func);

	mlx_ctx_t* mlxctx = mlx->context;
	mlxctx->key_hook.func = func;
	mlxctx->key_hook.param = param;
	glfwSetKeyCallback(mlx->window, mlx_key_callback);
}

bool mlx_is_key_down(t_mlx* mlx, t_keys key)
{
	MLX_NONNULL(mlx);

	return (glfwGetKey(mlx->window, key) == GLFW_PRESS);
}
