import { createWebHashHistory, createRouter } from "vue-router";
import Home from "@/views/Home.vue";
import WordPage from "@/views/WordPage.vue";
import Register from "@/views/Register.vue";
import Login from "@/views/Login.vue";
import Logout from "@/views/Logout.vue";
import CarrierePage from "@/views/CarrierePage.vue";
import Choice from "@/views/Choice.vue";
import ChoiceCarriere from "@/views/ChoiceCarriere.vue";
import HistoryPage from "@/views/HistoryPage.vue";
import ClassementPage from "@/views/ClassementPage.vue";
import axiosAuth from '@/api/axios-auth';
import axiosRefresh from '@/api/axios-refresh';
import Redirect from "@/views/Redirect.vue";

const routes = [
  {
    path: "/",
    name: "Home",
    component: Home,
    meta: {
      title: 'Wordchamp - Maison',
    },
  },
  {
    path: "/word/:i/:j",
    name: "Word",
    component: WordPage,
		meta: { 
      requiresAuth: true,
      title: 'Wordchamp - Le Jeu',
    }
  },
  {
    path: "/carriere/:i",
    name: "Carriere",
    component: CarrierePage,
		meta: { 
      requiresAuth: true,
      title: "Wordchamp - Le défi",
    }
  },
  {
    path: "/register",
    name: "Register",
    component: Register,
    meta: {
      title: 'Wordchamp - Enregistrement',
    }
  },
  {
    path: "/login",
    name: "Login",
    component: Login,
    meta: {
      title: 'Wordchamp - Connection',
    }
  },
  {
    path: "/logout",
    name: "Logout",
    component: Logout,
    meta: {
      title: 'Wordchamp - Déconnection',
    }
  },
  {
    path: "/choice",
    name: "choice-page",
    component: Choice,
    meta: { 
      requiresAuth: true,
      title: 'Blue or red pill ?',
    }
  },
  {
    path: "/choicecarriere",
    name: "choicecarriere-page",
    component: ChoiceCarriere,
    meta: { 
      requiresAuth: true,
      title: 'Blue or red pill ?',
    }
  },
  {
    path: "/redirect",
    name: "redirect-page",
    component: Redirect,
    meta: { 
      requiresAuth: true,
      title: 'Redirect ...',
    }
  },
  {
    path: "/history",
    name: "history-page",
    component: HistoryPage,
    meta: {
      requiresAuth: true,
      title: 'Wordchamp - Historique',
    }
  },
  {
    path: "/classement",
    name: "classment-page",
    component: ClassementPage,
    meta: {
      title: 'Wordchamp - Classement',
    }
  },
];

const router = createRouter({
  history: createWebHashHistory(),
  routes,
});

async function refresh_token() {
  const path = `${process.env.VUE_APP_BACKEND_URL}/refresh`;
  try {
    let response = await axiosRefresh.post(path)
    localStorage.setItem('token', response.data.token);
    localStorage.setItem('refresh_token', response.data.refresh_token);
    localStorage.setItem('id', response.data.id);
    localStorage.setItem('username', response.data.username);
    return true
  } catch(e) {
    return false
  }
}

router.beforeEach(async (to, from, next) => {
  let token = localStorage.getItem('token');
	let requireAuth = to.matched.some(record => record.meta.requiresAuth);

	if (!requireAuth) {
		next();
    return;
	}

	if (requireAuth && !token) {
		next('/login');
    return;
	}

	if (to.path === '/login') {
		if (token) {
      try {
        await axiosAuth.post('/verify-token')
        next('/');
      } catch (e) {
        if (refresh_token()) {
          next('/');
          return
        }
				next();
      } 
      return
		} else {
			next();
      return;
		}
	}

	if (requireAuth && token) {
    try {
      await axiosAuth.post('/verify-token')
      next();
    } catch (e) {
      if (refresh_token()) {
        next();
        return
      }
      next('/login');
    }
    return
	}
  if (token) {
    try {
      await axiosAuth.post('/verify-token')
      next();
    } catch (e) {
      if (refresh_token()) {
        next();
        return
      }
      next();
    }
    return
  }
});

async function hasGame() {
	const pathCG = `${process.env.VUE_APP_BACKEND_URL}/currentGame`
	try {
		let res = await axiosAuth.get(pathCG);
		return res.data	
	} catch (e) {
		return false
	}
}

router.beforeEach(async (to, from, next) => {
  if(to.path == "/choice") {
    if (await(hasGame())) {
      next("/word/:5/:6")
    } else  {
      next()
    }
    return
  }
  if(to.path == "/word") {
    if (await(hasGame())) {
      next("/word/:5/:6")
    } else  {
      next("/choice")
    }
    return
  }
  next()
});

async function hasGamecarriere() {
	const pathCG = `${process.env.VUE_APP_BACKEND_URL}/currentGamecarriere`
	try {
		let res = await axiosAuth.get(pathCG);
		return res.data	
	} catch (e) {
		return false
	}
}

router.beforeEach(async (to, from, next) => {
  if(to.path == "/choicecarriere") {
    if (await(hasGamecarriere())) {
      next("/carriere/:0")
    } else  {
      next()
    }
    return
  }
  if(to.path == "/carriere") {
    if (await(hasGamecarriere())) {
      next("/carriere/:0")
    } else  {
      next("/choicecarriere")
    }
    return
  }
  next()
});

router.beforeEach((to, from, next) => {
  const nearestWithTitle = to.matched.slice().reverse().find(r => r.meta && r.meta.title);
  const nearestWithMeta = to.matched.slice().reverse().find(r => r.meta && r.meta.metaTags);
  const previousNearestWithMeta = from.matched.slice().reverse().find(r => r.meta && r.meta.metaTags);

  // If a route with a title was found, set the document (page) title to that value.
  if(nearestWithTitle) {
    document.title = nearestWithTitle.meta.title;
  } else if(previousNearestWithMeta) {
    document.title = previousNearestWithMeta.meta.title;
  }

  // Remove any stale meta tags from the document using the key attribute we set below.
  Array.from(document.querySelectorAll('[data-vue-router-controlled]')).map(el => el.parentNode.removeChild(el));

  // Skip rendering meta tags if there are none.
  if(nearestWithMeta) {
    // Turn the meta tag definitions into actual elements in the head.
    nearestWithMeta.meta.metaTags.map(tagDef => {
      const tag = document.createElement('meta');

      Object.keys(tagDef).forEach(key => {
        tag.setAttribute(key, tagDef[key]);
      });

      // We use this to track which meta tags we create so we don't interfere with other ones.
      tag.setAttribute('data-vue-router-controlled', '');

      return tag;
    })
    // Add the meta tags to the document head.
    .forEach(tag => document.head.appendChild(tag));
  }
  next()
});

export default router;
