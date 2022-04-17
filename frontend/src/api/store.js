import axios from 'axios'
import router from '@/router'

const state = {
	username: null,
	token: null,
};

const mutations = {
	authUser(state, userData) {
		state.username = userData.username;
		state.token = userData.token;
	},
	clearAuthData(state) {
		state.username = null;
		state.token = null;
	},
};

const getters = {
	isAuthenticated(state) {
		return state.token !== null;
	},
};

const actions = {
	login: ({commit}, authData) => {
        const path = `${process.env.VUE_APP_BACKEND_URL}/login`;
        console.log("pinging " + path);
		axios.post(path, authData).then(response => {
            console.log("done pinging " + path);

            commit('authUser', { username: authData.username, token: response.data.token });
            localStorage.setItem('token', response.data.token);
            localStorage.setItem('username', authData.username);
            console.log(`Logged in as ${authData.username} with token ${response.data.token}`);
            router.replace('/');
		}).catch(error => {
            console.log("done pinging " + path);
			console.log(error);
		})
	},
	autoLogin({commit}) {
		let token = localStorage.getItem('token');
		let username = localStorage.getItem('username');

		if (!token || !username) {
			return;
		}

		commit('authUser', { username: username, token: token });
	},
	logout: ({commit}) => {
		commit('clearAuthData');
		localStorage.removeItem('username');
		localStorage.removeItem('token');
		router.replace('login');
	},
};

export default {
	namespaced: true,
	state,
	mutations,
	getters,
	actions,
}