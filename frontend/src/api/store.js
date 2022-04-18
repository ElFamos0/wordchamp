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
		state.id = userData.id;
	},
	clearAuthData(state) {
		state.username = null;
		state.token = null;
		state.id = null;
	},
};

const getters = {
	isAuthenticated(state) {
		return state.token !== null;
	},
	getID(state) {
		return state.id;
	},
};

const actions = {
	login: ({commit}, authData) => {
        const path = `${process.env.VUE_APP_BACKEND_URL}/login`;
        console.log("pinging " + path);
		axios.post(path, authData).then(response => {
            console.log("done pinging " + path);
			console.log(response)
            commit('authUser', { username: authData.username, id: response.data.id, token: response.data.token });
            localStorage.setItem('token', response.data.token);
            localStorage.setItem('id', response.data.id);
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
		let id = localStorage.getItem('id');

		if (!token || !username || !id) {
			return;
		}

		commit('authUser', { username: username, id: id, token: token });
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