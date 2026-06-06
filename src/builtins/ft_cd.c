
#include "builtins.h"
#include "utils.h"

#ifndef PATH_MAX
# define PATH_MAX 4096
#endif

static char	*get_home_directory(t_shell_state *state)
{
	char	*home;

	home = get_env_value_from_state(state, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (NULL);
	}
	return (ft_strdup(home));
}

static char	*get_target_directory(int argc, char **argv, t_shell_state *state)
{
	char	*oldpwd;

	if (argc == 1)
		return (get_home_directory(state));
	if (ft_strcmp(argv[1], "-") == 0)
	{
		oldpwd = get_env_value_from_state(state, "OLDPWD");
		if (!oldpwd)
		{
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		return (ft_strdup(oldpwd));
	}
	return (ft_strdup(argv[1]));
}

static char	*save_current_pwd(t_shell_state *state)
{
	char	current_pwd[PATH_MAX];
	char	*old_pwd;

	if (getcwd(current_pwd, sizeof(current_pwd)))
		old_pwd = ft_strdup(current_pwd);
	else
		old_pwd = get_env_value_from_state(state, "PWD");
	return (old_pwd);
}

static void	update_pwd_vars(t_shell_state *state, char *old_pwd)
{
	char	current_pwd[PATH_MAX];

	if (old_pwd)
	{
		set_env_value_in_state(state, "OLDPWD", old_pwd);
		if (old_pwd != get_env_value_from_state(state, "PWD"))
			free(old_pwd);
	}
	if (getcwd(current_pwd, sizeof(current_pwd)))
		set_env_value_in_state(state, "PWD", current_pwd);
}

int	ft_cd(int argc, char **argv, t_shell_state *state)
{
	char	*target;
	char	*old_pwd;

	target = get_target_directory(argc, argv, state);
	if (!target)
		return (1);
	old_pwd = save_current_pwd(state);
	if (chdir(target) == -1)
	{
		print_cd_error(target);
		free(target);
		if (old_pwd != get_env_value_from_state(state, "PWD"))
			free(old_pwd);
		return (1);
	}
	update_pwd_vars(state, old_pwd);
	free(target);
	return (0);
}
