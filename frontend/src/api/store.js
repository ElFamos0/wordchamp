import axios from 'axios'
import router from '@/router'

const state = {
	username: null,
	id: null,
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
        const path = `${process.env.VUE_APP_BACKEND_URL}/login`;
		axios.post(path, authData).then(response => {
            commit('authUser', { username: authData.username, id: response.data.id, token: response.data.token });
            localStorage.setItem('token', response.data.token);
            localStorage.setItem('id', response.data.id);
            localStorage.setItem('username', authData.username);
            router.replace('/');
		}).catch(error => {
			console.log(error);
		})
	},
	autoLogin({commit}) {
		console.log('autoLogin');
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