import axios from 'axios';
import axiosRefresh from './axios-refresh';
import router from '@/router';

function refresh_token() {
	const path = `${process.env.VUE_APP_BACKEND_URL}/refresh`;
	axiosRefresh.post(path)
		.then(response => {
			localStorage.setItem('token', response.data.token);
			localStorage.setItem('refresh_token', response.data.refresh_token);
			localStorage.setItem('id', response.data.id);
			localStorage.setItem('username', response.data.username);
			return true
		})
		.catch(() => {
			return false
		});
}

const state = {
	username: null,
	id: null,
	token: null,
	refresh_token: null,
};

const mutations = {
	authUser(state, userData) {
		state.username = userData.username;
		state.token = userData.token;
		state.refresh_token = userData.refresh_token;
		state.id = userData.id;
	},
	clearAuthData(state) {
		state.username = null;
		state.token = null;
		state.refresh_token = null;
		state.id = null;
	},
	changeUsername(state, username) {
		state.username = username;
	}
};

const getters = {
	isAuthenticated(state) {
		return state.token !== null;
	},
	getID(state) {
		return state.id;
	},
	getUsername(state) {
		return state.username;
	}
};

const actions = {
	login: ({commit}, authData) => {
		return new Promise((resolve, reject) => {
			const path = `${process.env.VUE_APP_BACKEND_URL}/login`;
			axios.post(path, authData).then(response => {
				commit('authUser', { username: authData.username, id: response.data.id, token: response.data.token, refresh_token: response.data.refresh_token });
				localStorage.setItem('token', response.data.token);
				localStorage.setItem('refresh_token', response.data.refresh_token);
				localStorage.setItem('id', response.data.id);
				localStorage.setItem('username', response.data.username);
				router.replace('/');
				resolve()
			}).catch(() => {
				if (!refresh_token()) {
					reject('cannot log in');
				}
			})
		})
	},
	autoLogin({commit}) {
		// console.log('autoLogin');
		let token = localStorage.getItem('token');
		let refresh_token = localStorage.getItem('refresh_token');
		let username = localStorage.getItem('username');
		let id = localStorage.getItem('id');

		if (!refresh_token || !token || !username || !id) {
			return;
		}

		commit('authUser', { username: username, id: id, token: token, refresh_token: refresh_token });
	},
	logout: ({commit}) => {
		commit('clearAuthData');
		localStorage.removeItem('id');
		localStorage.removeItem('username');
		localStorage.removeItem('token');
		localStorage.removeItem('refresh_token');
		router.replace('login');
	},
	changeUsername: ({commit}, username) => {
		commit('changeUsername', username);
	},
};

export default {
	namespaced: true,
	state,
	mutations,
	getters,
	actions,
}