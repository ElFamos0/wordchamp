import { createWebHashHistory, createRouter } from "vue-router";
import Home from "@/views/Home.vue";
import Random from "@/views/Random.vue";
import Word from "@/views/Word.vue";
import Register from "@/views/Register.vue";
import Login from "@/views/Login.vue";
import Logout from "@/views/Logout.vue";
import Profile from "@/views/Profile.vue";

import ProfileMain from "@/components/ProfileMain.vue";
import axiosAuth from '@/api/axios-auth'

const routes = [
  {
    path: "/",
    name: "Home",
    component: Home,
  },
  {
    path: "/random",
    name: "About",
    component: Random,
  },
  {
    path: "/word",
    name: "Word",
    component: Word,
		meta: { requiresAuth: true }
  },
  {
    path: "/register",
    name: "Register",
    component: Register,
  },
  {
    path: "/login",
    name: "Login",
    component: Login,
  },
  {
    path: "/logout",
    name: "Logout",
    component: Logout,
  },
  {
    path: "/profile",
    name: "Profile",
    component: Profile,
    children: [
      {
        path: '',
        component: ProfileMain,
      },
      {
        path: 'historique',
        component: ProfileMain,
      },
    ],
  },
];

const router = createRouter({
  history: createWebHashHistory(),
  routes,
});


router.beforeEach((to, from, next) => {
	let token = localStorage.getItem('token');
	let requireAuth = to.matched.some(record => record.meta.requiresAuth);

	if (!requireAuth) {
		next();
	}

	if (requireAuth && !token) {
		next('/login');
	}

	if (to.path === '/login') {
		if (token) {
			axiosAuth.post('/verify-token').then(() => {
				next('/word');
			}).catch(() => {
				next();
			});
		}
		else {
			next();
		}
	}

	if (requireAuth && token) {
		axiosAuth.post('/verify-token').then(() => {
			next();
		}).catch(() => {
			next('/login');
		})
	}
});

export default router;
