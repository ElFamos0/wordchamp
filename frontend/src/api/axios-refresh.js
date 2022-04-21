import axios from 'axios'

const instance = axios.create({
    baseURL: process.env.VUE_APP_BACKEND_URL,
    headers: {
        'Authorization': {
            toString() {
                return `Bearer ${localStorage.getItem('refresh_token')}`
            }
        }
    }
});

export default instance